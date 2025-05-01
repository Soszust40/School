/**
 * @file InvisibleAnswer.h
 * @author Jackson White
 *
 * This class holds the information about what the answer to the game is
 */

#ifndef INVISIBLEANSWER_H
#define INVISIBLEANSWER_H

#include <complex.h>

class Item;
class Letter;

/**
 * Holds information about the answer to the game.
 */
class InvisibleAnswer {
private:
    /// The column that answer starts at
    double mCol;
    /// The row the answer starts at
    double mRow;
    /// The number of letters in the answer;
    int mLength;
    /// The answer as a list of integers
    std::vector<int> mAnswer;
    /// The users solution
    std::vector<int> mSolution;
public:
    void XmlLoad(wxXmlNode* xmlNode);
    bool HitTest(double x, double y);
    bool InSolution(Letter* letter);
    bool SpotFilled(std::shared_ptr<Item> letter, double x);
    void RemoveFromSolution(std::shared_ptr<Item> letter);
    void AddGivenToSolution(std::shared_ptr<Item> given);
    bool IsComplete();
    void Solve(std::shared_ptr<Item> letter);
    bool FilledOut();
    int CorrectLetters();
    int WrongSpot();
};

#endif //INVISIBLEANSWER_H
