/**
 * @file Item.h
 * @author Aditya Menon
 * @author Jackson White
 * Base class for all items in the game.
 */

#ifndef MAHJONG_SPARTANMIND_ITEM_H
#define MAHJONG_SPARTANMIND_ITEM_H

#include "ItemVisitor.h"
#include <memory>

class ItemVisitor;
class Picture;
class Game;

/**
 * Base class for all items in the game.
 */
class Item {
private:
    /// The id of the item
    std::string mId;
    /// The current column the item is at (bottom left)
    double mCol = 0;
    /// The current row the item is at (bottom left)
    double mRow = 0;
    /// The width of the item
    int mWidth = 48;  ///< Value will be overriden when loading (every time), but when Testing we need 48
    /// The height of the item
    int mHeight = 48; /// < Value will be overriden when loading (every time), but when Testing we need 48

    /// The underlying image
    std::shared_ptr<wxImage> mItemImage = nullptr;
    
    /// The bitmap we can display for this item
    std::shared_ptr<wxBitmap> mItemBitmap = nullptr;

    /// The game that item is in
    Game *mGame = nullptr;

public:
    /**
     * Function that returns a pointer the game object.
     *
     * @return Pointer to the game object.
     */
    Game * GetGame() { return mGame; };
    /**
     * Handle updates for animation.
     *
     * @param elapsed The time since the last update.
     */
    virtual void Update(double elapsed) {}

    /**
     * Accept a visitor.
     *
     * @param visitor The visitor we accept.
     */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * What the items should do when the left key is clicked.
     * Implemented only in player class.
     *
     * @param screenX X coordinate.
     * @param screenY Y coordinate.
     */
    virtual void OnLeftDown(double screenX, double screenY) {}

    /**
     * Get the width of the item.
     * @return Width in pixels.
     */
    int GetWidth() const {return mWidth;}

    /**
     * Get the height of the item.
     * @return Height in pixels.
     */
    int GetHeight() const {return mHeight;}

    virtual bool HitTest(double x, double y);

    /**
     * Destructor
     */
    virtual ~Item();

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    virtual void XmlLoad(wxXmlNode *node, wxXmlNode *declaration);

    /**
     * Set the item location.
     * @param x X location in pixels.
     * @param y Y location in pixels.
     */
    virtual void SetLocation(double x, double y) { mCol = x; mRow = y; }

    /**
     * Get the id of the item.
     * @return id.
     */
    std::string GetId() const {return mId;}
    /**
     * Get the X location of the item.
     * @return X location in pixels.
     */
    double GetX() const { return mCol; }

    /**
     * Get the Y location of the item.
     * @return Y location in pixels.
     */
    double GetY() const { return mRow; }

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

protected:
    Item(Game *game, const std::wstring &filename);
};

#endif //MAHJONG_SPARTANMIND_ITEM_H 