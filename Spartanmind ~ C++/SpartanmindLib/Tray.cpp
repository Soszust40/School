/**
 * @file Tray.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "Tray.h"
#include "Game.h"
#include "Letter.h"
#include <random>
#include <vector>
#include <algorithm>

#include "LetterCoordVisitor.h"
#include "LetterInTrayDrawer.h"
#include "LetterTrayCoordinateSetterVisitor.h"

/// Tray image filename
const std::wstring TrayImageName = L"images/tray.png";

using namespace std;

/**
 * Constructor for the Tray class.
 * @param game The game this tray is a part of.
 * @param filename The tray image filename.
 */
Tray::Tray(Game* game, const std::wstring& filename) : Item(game, filename)
{

}

/**
 * Add a letter to the tray.
 * @param letter Letter to add.
 * @return True if letter was added, false if tray is full.
 */
bool Tray::AddLetter(std::shared_ptr<Item> letter)
{
    if (IsFull())
    {
        return false;
    }
    
    // Define boundaries for random placement
    const double minX = .2;
    const double maxX = (GetWidth() -10) / GetGame()->TileWidth();
    const double minY = (-GetHeight() + 15) / GetGame()->TileHeight();
    const double maxY = -.15;

    // Define boundary for random placement
    const double minDistance = 0.7; // Minimum distance between letters

    // Generate random position
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distX(minX, maxX);
    std::uniform_real_distribution<double> distY(minY, maxY);

    double newX = 0, newY = 0;

    bool validPosition = false;
    int attempts = 0;
    const int maxAttempts = 50;

    // Try to find a non-overlapping position
    while (!validPosition && attempts < maxAttempts)
    {
        newX = distX(gen);
        newY = distY(gen);

        validPosition = true;

        // Check distance from existing letters
        LetterCoordVisitor letterCoords;
        for (size_t i = 0; i < mLetters.size(); i++)
        {
            mLetters[i]->Accept(&letterCoords);
            double existingX = letterCoords.GetX();
            double existingY = letterCoords.GetY();
            
            double distance = std::sqrt(
                std::pow(newX - existingX, 2) + 
                std::pow(newY - existingY, 2)
            );

            if (distance < minDistance)
            {
                validPosition = false;
                break;
            }
        }
        attempts++;
    }

    // Set the letter's position
    LetterTrayCoordinateSetterVisitor letterCordSetter(newX, newY);
    letter->Accept(&letterCordSetter);
    mLetters.push_back(letter);
    
    return true;
}

/**
 * Remove a letter from the tray.
 * @param letter Letter to remove.
 * @return True if letter was found and removed, false otherwise.
 */
bool Tray::RemoveLetter(const std::shared_ptr<Item> letter)
{
    auto it = std::find(mLetters.begin(), mLetters.end(), letter);
    if (it != mLetters.end())
    {
        mLetters.erase(it);
        return true;
    }
    
    return false;
}

/**
 * Check if the tray contains a specific letter.
 * @param letter Letter to check for.
 * @return True if letter is in tray, false otherwise.
 */
bool Tray::ContainsLetter(const std::shared_ptr<Item> letter) const
{
    return std::find(mLetters.begin(), mLetters.end(), letter) != mLetters.end();
}

/**
 * Load the Item.
 * @param node The item node.
 * @param declaration The declaration node.
 */
void Tray::XmlLoad(wxXmlNode *node, wxXmlNode *declaration)
{
    mLetters.clear();
    Item::XmlLoad(node, declaration);
    declaration->GetAttribute(L"capacity").ToInt(&mMaxCapacity);
}

/**
 * Draw the tray object.
 * @param graphics The graphic of the tray to be drawn.
 */
void Tray::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    graphics->PushState();

    // Define the tray bounds for letter placement
    graphics->Translate(GetX() * GetGame()->TileWidth(), GetY() * GetGame()->TileHeight());
    graphics->Scale(0.8, 0.8);

    LetterInTrayDrawer letterDrawer(graphics);
    // Draw each letter at its current position
    for (auto& letter : mLetters)
    {
        letter->Accept(&letterDrawer);
    }
    
    graphics->PopState();
}

/**
 * Drops a single letter.
 * @return Returns nullptr if list is empty, otherwise the dropped letter.
 */
std::shared_ptr<Item> Tray::DropSingleLetter()
{
    if (!mLetters.empty())
    {
        auto droppedLetter = mLetters.back();
        mLetters.pop_back();
        return droppedLetter;
    }

    return nullptr;
}