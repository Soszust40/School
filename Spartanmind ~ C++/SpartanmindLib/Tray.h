/**
 * @file Tray.h
 * @author Aditya Menon
 * @author Jackson White
 *
 * Class that represents the letter tray in the Spartanmind game
 */

#ifndef TRAY_H
#define TRAY_H

#include "Item.h"
#include <vector>
#include <string>
#include <memory>
#include <wx/wx.h>

class Game;
class Letter;
class wxGraphicsContext;

/**
 * Class that represents the letter tray in the game
 *
 * The tray displays letters that the player has grabbed
 * and is currently holding.
 */
class Tray : public Item
{
private:
    /// The letters currently in the tray.
    std::vector<std::shared_ptr<Item>> mLetters;

    /// Maximum capacity of the tray.
    int mMaxCapacity;

public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitTray(this); }
    Tray(Game* game, const std::wstring& filename);

    bool AddLetter(std::shared_ptr<Item> letter);

    bool RemoveLetter(std::shared_ptr<Item> letter);

    bool ContainsLetter(std::shared_ptr<Item> letter) const;

    /**
    * Drops a single letter from the tray.
    * @return The letter that was dropped or nullptr if tray is empty.
    */
    std::shared_ptr<Item> DropSingleLetter();

    /**
     * Check if the tray is full.
     *
     * @return Bool if the tray is full.
     */
    bool IsFull() const { return mLetters.size() >= mMaxCapacity; }

    /**
     * Get the amount of letters in the tray.
     *
     * @return Int of the amount of letters.
     */
    int GetLetterCount() const { return mLetters.size(); }

    /**
     * Get the capacity of the Tray.
     *
     * @return Int of the capacity.
     */
    int GetCapacity() const { return mMaxCapacity; }

    void XmlLoad(wxXmlNode *node, wxXmlNode *declaration) override;

    /**
     * Get all letters currently in the tray.
     *
     * @return Vector of letters.
     */
    const std::vector<std::shared_ptr<Item>> GetLetters() const { return mLetters; }

    /**
     * Clear all letters from the tray.
     */
    void Clear() { mLetters.clear(); }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
}; 

#endif //TRAY_H