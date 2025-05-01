/**
 * @file Container.cpp
 * @author Myles Walker
 */

#include "pch.h"
#include "Container.h"
#include "Game.h"
#include "Letter.h"
#include "Picture.h"
#include <random>
using namespace std;

/**
 * Constructor
 * @param game The game this container is part of.
 * @param filename The image filename for the container.
 * @param filenameFront The front image of the container.
 */
Container::Container(Game* game, const std::wstring& filename, const std::wstring& filenameFront) : Item(game, L"")
{
    auto picture1 = GetGame()->GetCachedPicture(filename);
    auto picture2 = GetGame()->GetCachedPicture(filenameFront);
    mFirstImage = picture1->GetImage();
    mFrontImage = picture2->GetImage();
    mFirstBitmap = picture1->GetBitmap();
    mFrontBitmap = picture2->GetBitmap();
}

/**
 * Add a letter to this container.
 * @param letter Letter to add.
 */
void Container::AddLetter(const std::shared_ptr<Item>& letter)
{
    mLetters.push_back(letter);
}

/**
 * Release the letters into the playing area.
 */
void Container::ReleaseLetters()
{
    double containerX = GetX();
    double containerY = GetY();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> offsetX(-2.0, 2.0);
    std::uniform_real_distribution<> offsetY(-6.0, -3.0);

    double spacing = 0.7; // Minimum space between letters
    double currentX = containerX;

    /// loop through stored letters
    for (auto& letter : mLetters)
    {
        /// randomly put in nearby position left right and up and down
        double newX = currentX + offsetX(gen);
        double newY = containerY + offsetY(gen);

        letter->SetLocation(newX, newY);
        GetGame()->AddItem(letter);
        currentX += spacing;
    }
    mLetters.clear();
}

/**
 * Draw the container.
 * @param graphics Graphics context to draw on.
 */
void Container::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // 1) Ensure bitmaps are initialized
    if (mFirstBitmap->IsNull())
    {
        mFirstBitmap = make_shared<wxBitmap>(*mFirstImage);
    }
    if (mFrontBitmap->IsNull())
    {
        mFrontBitmap = make_shared<wxBitmap>(*mFrontImage);
    }

    graphics->PushState();

    int pixelWidth = GetWidth();
    int pixelHeight = GetHeight();

    // Get dimensions for the second image
    int secondWidth = mFrontImage->GetWidth();
    int secondHeight = mFrontImage->GetHeight();

    graphics->DrawBitmap(*mFirstBitmap,GetX() * GetGame()->TileHeight(), (GetY() + 1) * GetGame()->TileWidth() - pixelHeight, pixelWidth, pixelHeight);
    graphics->PopState();

    // If container NOT open draw letters inside
    if (!mIsOpened)
    {
        for (const auto& item : mLetters)
        {
            item->Draw(graphics);
        }
    }

    graphics->PushState();
    graphics->Translate(GetX() * GetGame()->TileWidth(), (GetY()+1) * GetGame()->TileHeight() - secondHeight);
    graphics->DrawBitmap(*mFrontBitmap, 0, 0, secondWidth, secondHeight);

    graphics->PopState();
}

/**
 * Load the container from XML.
 * @param node XML item node.
 * @param declaration XML declaration node.
 */
void Container::XmlLoad(wxXmlNode* node, wxXmlNode* declaration)
{
    mLetters.clear();
    mIsOpened = false;
    Item::XmlLoad(node, declaration);
}

/**
 * This function is that is called when we headbutt.
 * The container. We need to open the container and release the letters.
 */
void Container::HandleHeadbutt()
{
    if (!mIsOpened)
    {
        OpenContainer();
        ReleaseLetters();
        mLetters.clear();
    }
}