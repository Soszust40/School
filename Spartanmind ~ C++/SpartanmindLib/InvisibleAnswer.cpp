/**
 * @file InvisibleAnswer.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "InvisibleAnswer.h"
#include "sstream"
#include "Item.h"
#include "LetterVisitorValue.h"
#include "GivenValueVisitior.h"
#include "Letter.h"

using namespace std;

/**
 * Load information from the xml document that gives us the answer.
 * @param node The node with information of the answer.
 */
void InvisibleAnswer::XmlLoad(wxXmlNode* node)
{
    node->GetAttribute(L"col").ToDouble(&mCol);
    node->GetAttribute(L"row").ToDouble(&mRow);
    node->GetAttribute(L"length").ToInt(&mLength);

    auto lettersNode = node->GetChildren();
    auto answersInformation = lettersNode->GetContent().ToStdString();

    istringstream stream(answersInformation);
    int num;

    while (stream >> num)
    {
        mSolution.push_back(-99);
        mAnswer.push_back(num);
    }
}

/**
 * Checks if we are inside one of the answer spots.
 *
 * @param x The X coordinate to hittest.
 * @param y The Y coordinate to hittest.
 * @return If we are inside the answer spots.
 */
bool InvisibleAnswer::HitTest(double x, double y)
{
    if (mCol <= x && x <= mCol + mLength && mRow <= y && y <= mRow + 1 )
    {
        return true;
    }
    return false;
}

/**
 * Checks if the letter is in the solution.
 *
 * @param letter The letter we are checking.
 * @return Bool of if the letter is already in the solution.
 */
bool InvisibleAnswer::InSolution(Letter* letter)
{
    int x = letter->GetX();
    int y = letter->GetY();
    if (mCol <= x && x <= mCol + mLength && y == mRow)
    {
        return true;
    }
    return false;
}

/**
 * Checks if the spot was filled or not.
 *
 * @param letter The letter we are trying to fill the spot with.
 * @param x Position x coordinate.
 * @return Bool of if the spot is filled or not.
 */
bool InvisibleAnswer::SpotFilled(shared_ptr<Item> letter, double x)
{
    x = floor(x);
    x = x - mCol;
    x = static_cast<int>(x);
    if (mSolution[static_cast<int>(x)] == -99)
    {
        LetterVisitorValue letterVisitor;
        letter->Accept(&letterVisitor);
        mSolution[x] = letterVisitor.LetterValue();
        return false;
    }

    return true;
}

/**
 * Remove a letter from the solution when it is picked up.
 *
 * @param letter a pointer to the letter we want to remove.
 */
void InvisibleAnswer::RemoveFromSolution(shared_ptr<Item> letter)
{
    auto x = letter->GetX();
    auto newSpot = letter->GetX()-mCol;
    mSolution[static_cast<int>(newSpot)] = -99;
}

/**
 * Adds the given that stays in place to the solution.
 * @param given The given to add to the solution.
 */
void InvisibleAnswer::AddGivenToSolution(shared_ptr<Item> given)
{
    auto xSpot = given->GetX();
    GivenValueVisitior givenValue;
    given->Accept(&givenValue);

    if (givenValue.GetValue() != -99)
    {
        mSolution[static_cast<int>(xSpot - mCol)] = static_cast<int>(givenValue.GetValue());
    }
}

/**
 * Check if the solution matches the answer in other words, is the game complete?
 *
 * @return True if the game is complete.
 */
bool InvisibleAnswer::IsComplete()
{
    return mSolution == mAnswer;
}

/**
 * Checks if the letter is part of the solution.
 * If it is, then we move it to the correct spot, and we add it to the solution.
 *
 * @param letter the letter we are trying to use to solve the game.
 */
void InvisibleAnswer::Solve(shared_ptr<Item> letter)
{

    LetterVisitorValue letterVisitor;
    letter->Accept(&letterVisitor);
    int value = letterVisitor.LetterValue();
    for (int i = 0; i < mLength; i++)
    {
        if (value == mAnswer[i] && mSolution[i] == -99)
        {
            letter->SetLocation(i + mCol, mRow);
            mSolution[i] = value;
            return;
        }
    }
}

/**
 * Check if all slots of the game are filled out.
 *
 * @return True if the game is filled out, false otherwise.
 */
bool InvisibleAnswer::FilledOut()
{
    for (int i = 0 ; i < mLength; i++)
    {
        if (mSolution[i] == -99)
        {
            return false;
        }
    }
    return true;
}

/**
 * Get the number of letters in the right spot.
 *
 * @return The number of correct letters.
 */
int InvisibleAnswer::CorrectLetters()
{
    int correct = 0;
    for (int i = 0 ; i < mLength; i++)
    {
        if (mSolution[i] == mAnswer[i])
        {
            correct++;
        }
    }
    return correct;
}

/**
 * Get the number of letters in the wrong spot.
 * @return The amount of letters in the wrong spot.
 */
int InvisibleAnswer::WrongSpot()
{
    int wrongSpot = 0;
    for (int i = 0 ; i < mLength; i++)
    {
        if (mSolution[i] != mAnswer[i])
        {
            if (find(mAnswer.begin(), mAnswer.end(), mSolution[i]) != mAnswer.end())
            {
                wrongSpot++;
            }
        }
    }
    return wrongSpot;
}