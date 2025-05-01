/**
 * @file Letter.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "Letter.h"
#include "Picture.h"
#include <chrono>

#include "Game.h"
#include "Item.h"

using namespace std;

/**
 * Constructor for the Letter class.
 * @param game The game this item is a member of.
 * @param imageName The filename of the image for the item.
 */
Letter::Letter(Game *game, const std::wstring &imageName) : Item(game, imageName)
{
    auto picture = game->GetCachedPicture(imageName);
    mItemImage = picture->GetImage();
    mItemBitmap = picture->GetBitmap();
}

/**
 * Load a letter in. UpCall from Item class, and then store the value of Letter.
 *
 * @param node The item node.
 * @param declaration The declaration node.
 */
void Letter::XmlLoad(wxXmlNode *node, wxXmlNode *declaration)
{
    Item::XmlLoad(node, declaration);
    declaration->GetAttribute(L"value").ToInt(&mValue);
}

/**
 * Draw the letter that is inside the tray based on its Tray coordinates
 *
 * @param graphics the graphics we are drawing to
 */
void Letter::DrawInTray(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap->IsNull())
    {
        mItemBitmap = make_shared<wxBitmap>(*mItemImage);
    }
    int pixelWidth = GetWidth();
    int pixelHeight = GetHeight();

    graphics->PushState();

    auto x = GetX()* GetGame()->TileHeight();
    auto y = (GetY() + 1) * GetGame()->TileWidth()  - pixelHeight;
    auto s = pixelWidth;
    auto a = pixelHeight;
    graphics->DrawBitmap(*mItemBitmap, mTrayX* GetGame()->TileHeight(), (mTrayY + 1) * GetGame()->TileWidth()  - pixelHeight, pixelWidth, pixelHeight);

    graphics->PopState();
}