/**
 * @file Container.h
 * @author Myles Walker
 */
 
#pragma once

#include "Item.h"
#include <vector>
#include <memory>
#include <string>
#include <wx/wx.h>

class Game;
class Letter;
class ItemVisitor;
class wxGraphicsContext;

/**
 * Class that represents a container holding letters.
 *
 * Letters are stored inside the container and released when SPARTY headbutts the container.
 */
class Container : public Item {
private:
    /// The letters stored inside the container
    std::vector<std::shared_ptr<Item>> mLetters;
    /// First image for the Container
    std::shared_ptr<wxImage> mFirstImage = nullptr;
    /// First bitmap we can display
    std::shared_ptr<wxBitmap> mFirstBitmap = nullptr;
    /// Front image of the container
    std::shared_ptr<wxImage> mFrontImage = nullptr;
    /// Second bitmap we can display
    std::shared_ptr<wxBitmap> mFrontBitmap = nullptr;
    /// check if opened or not
    bool mIsOpened = false;

public:
    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitContainer(this); }

    ///Constructor
    Container(Game* game, const std::wstring& filename, const std::wstring& filenameFront);

    /**
     * open the container
     */
    void OpenContainer() { mIsOpened = true; }

    void AddLetter(const std::shared_ptr<Item>& letter);

    void ReleaseLetters();

    /**
     * Get all letters currently in the container.
     * @return Vector of letters.
     */
    const std::vector<std::shared_ptr<Item>> GetLetters() const { return mLetters; }

    /**
     * Clear all letters from the container.
     */
    void Clear() { mLetters.clear(); }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node, wxXmlNode* declaration) override;

    /**
     * Function that returns if the container is opened or not.
     * @return Returns true of false depending on if the container is open or not.
     */
    bool IsOpened() const { return mIsOpened; }

    void HandleHeadbutt();
};




