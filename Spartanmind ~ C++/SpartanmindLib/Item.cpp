/**
 * @file Item.cpp
 * @author Aditya Menon
 * @author Jackson White
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include "Picture.h"

using namespace std;

/**
 * Constructor for the Item class.
 * @param game The game this item is a member of.
 * @param filename The filename of the image for the item.
 */
Item::Item(Game *game, const std::wstring &filename) : mGame(game)
{
    if (filename != "")
    {
        auto picture = mGame->GetCachedPicture(filename);
        mItemImage = picture->GetImage();
        mItemBitmap = picture->GetBitmap();
    }
}

/**
 * Destructor for Items.
 */
Item::~Item()
{

}

/**
 * Draw this item.
 * @param graphics Graphics context to draw on.
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap->IsNull())
    {
        mItemBitmap = make_shared<wxBitmap>(*mItemImage);
    }
    int pixelWidth = GetWidth();
    int pixelHeight = GetHeight();

    graphics->PushState();

    graphics->DrawBitmap(*mItemBitmap, GetX()* mGame->TileHeight(), (GetY() + 1) * mGame->TileWidth()  - pixelHeight, pixelWidth, pixelHeight);

    graphics->PopState();
}

/**
 * Test to see if we hit this object with a mouse click.
 * @param x X position to test.
 * @param y Y position to test.
 * @return True if we hit an item.
 */
bool Item::HitTest(double x, double y)
{
    auto spotX = GetX();
    auto spotY = GetY();

    spotX *= mGame->TileWidth();
    spotY = (spotY+1) * mGame->TileHeight() - mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap
    spotX = x - spotX;
    spotY = y - spotY;

    // Test to see if x, y are in the image
    if (spotX < 0 || spotY < 0 || spotX >= mItemImage->GetWidth() || spotY >= mItemImage->GetHeight())
    {
        // Outside the image
        return false;
    }
    return !mItemImage->IsTransparent((int)spotX, (int)spotY);
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from.
 * @param declaration The Xml node we are getting declaration information from.
 */
void Item::XmlLoad(wxXmlNode *node, wxXmlNode *declaration)
{
    auto x = node->GetAttribute(L"id");
    mId = node->GetAttribute(L"id").ToStdString();
    node->GetAttribute(L"col", L"0").ToDouble(&mCol);
    node->GetAttribute(L"row", L"0").ToDouble(&mRow);

    declaration->GetAttribute(L"width", L"0").ToInt(&mWidth);
    declaration->GetAttribute(L"height", L"0").ToInt(&mHeight);
}