/**
 * @file Game.cpp
 * @author Jackson White
 * @author Simon Oszust
 */

#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "obstacle.h"
#include "Tray.h"
#include "Loader.h"
#include "Picture.h"
#include "ContainerHeadButtVisitor.h"
#include "ContainerOpenVisitor.h"
#include "LetterPickerUpperVisitor.h"
#include "TrayAddLetterVisitor.h"
#include "TraysLettersVisitor.h"
#include "TrayRemoveLetterVisitor.h"
#include "LetterVisitorValue.h"
#include "InvisibleAnswer.h"
#include "LetterSolverVisitor.h"
#include "ObstacleVisitorHitTest.h"
#include "TrayDropOneLetterVisitor.h"
#include <wx/graphics.h>
#include <random>

/// tray filename
const std::wstring TrayImageName = L"images/tray.png";
/// first level xml level1
const std::wstring Level1 = L"levels/level1.xml";

using namespace std;

/**
 * Draw the game.
 * @param graphics Graphics device to draw on.
 * @param width Width of the window.
 * @param height Height of the window.
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    int pixelWidth = mWidth * mTileWidth;
    int pixelHeight = mHeight * mTileHeight;

    ///
    /// Automatic Scaling
    ///
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for (auto& item : mItems)
    {
        item->Draw(graphics);
    }
    mPlayer->Draw(graphics);

    /// Restore original state to prevent affecting other objects
    graphics->PopState();
}

/**
 * Game Constructor for the game object.
 */
Game::Game()
{
    /// move the newly created loader to the mLoad
    unique_ptr<Loader> load = make_unique<Loader>(this);
    mLoader = move(load);
    /// First load the level
    OnLoadLevel(Level1);
    mLevel = 1;
}

/**
 * Clears all items from the game.
 */
void Game::Clear()
{
    mItems.clear();
    mPlayer.reset();
}

/**
 * Add a player to the game class.
 * @param player Player to add.
 */
void Game::AddPlayer(shared_ptr<Player> player)
{
    mPlayer = player;
}

/**
 * Add letter/given to the game.
 * @param item The letter/given item we are adding to the game.
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 *  Function is called from the Event Handler for left flick.
 *
 * @param screenX X location of the mouse click.
 * @param screenY Y location of the mouse click.
 */
void Game::OnLeftDown(wxCoord screenX, wxCoord screenY)
{
    if (mIsFrozen)
    {
        return;
    }
    double oX = (screenX -  mXOffset) / mScale;
    double oY = (screenY - mYOffset) / mScale;

    if (oX <= mTileWidth * mWidth && oY <= mTileHeight * mHeight && oX >= 0 && oY >= 0)
    {
        mPlayer->OnLeftDown(oX, oY);
    }
}

/**
 * Load a Level of the game.
 * @param filename The file we are loading.
 */
void Game::OnLoadLevel(const wstring& filename)
{
    Clear();
    size_t pos = filename.find(L"s/level");
    if (pos == std::wstring::npos) return; // Not found

    pos += 7;
    mLevel = std::stoi(filename.substr(pos,1));
    mLoader->LoadLevel(filename);
}

/**
 * Load a game.
 * @param level The level to load the game from.
 */
void Game::XmlGame(wxXmlNode* level)
{
    level->GetAttribute(L"width").ToInt(&mWidth);
    level->GetAttribute(L"height").ToInt(&mHeight);
    level->GetAttribute(L"tilewidth").ToInt(&mTileWidth);
    level->GetAttribute(L"tileheight").ToInt(&mTileHeight);
}

/**
 * Test an x,y click location to see if it clicked on some item in the game.
 *
 * @param x X location in pixels.
 * @param y Y location in pixels.
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    double oX = (x -  mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    if (oX <= mTileWidth * mWidth && oY <= mTileHeight * mHeight && oX >= 0 && oY >= 0)
    {
        for (auto item = mItems.rbegin(); item != mItems.rend(); item++)
        {
            if ((*item)->HitTest(oX, oY))
            {
                return *item;
            }
        }
    }
    return nullptr;
}

/**
 * User has hit the spacebar.
 *
 * @return bool Is the chest full.
 */
bool Game::StartSpaceAnimation()
{
    if (mIsFrozen)
    {
        return false;
    }
    /// we need to calculate the players x and y spots
    auto playerX = mPlayer->GetX() * TileWidth() * mScale + mXOffset;
    auto playerY = mPlayer->GetY() * TileHeight() * mScale + mYOffset;
    playerX += mPlayer->GetTargetX() * mScale;
    playerY += mPlayer->GetTargetY() * mScale;

    mPlayer->StartOpenAnimation();

    /// pointer to the letter we want to remove
    auto letterToRemove = mItems.end();
    /// switch to screen coordinates
    double oX = (playerX -  mXOffset) / mScale;
    double oY = (playerY - mYOffset) / mScale;
    for (auto item = mItems.rbegin(); item != mItems.rend(); ++item)
    {
        /// letter picker upper visitor that will visit each letter
        LetterPickerUpperVisitor letterVisitor(oX, oY);
        (*item)->Accept(&letterVisitor);
        if (letterVisitor.PickedUpLetter())
        {
            /// need to iterate through whole list again and find tray
            /// tray visitor that tries to add the letter to the tray
            TrayAddLetterVisitor trayVisitor(*item);
            for (auto tray = mItems.rbegin(); tray != mItems.rend(); ++tray)
            {
                (*tray)->Accept(&trayVisitor);
            }

            if (!trayVisitor.AddedLetter())
            {
                return true;
            }
            letterToRemove = std::next(item).base();
            break;
        }
    }

    /// if we werent over a letter
    if (letterToRemove == mItems.end())
    {
        return false;
    }

    if (mAnswer->HitTest(oX / TileWidth(), oY / TileHeight()))
    {
        mAnswer->RemoveFromSolution(*letterToRemove);
    }

    if (letterToRemove != mItems.end())
    {
        mItems.erase(letterToRemove);
    }

    return false;
}

/**
 * This function checks if the player has headbutt the container.
 *
 * @param container The container item.
 * @return Returns true if the player collides with the container.
 */
bool Game::SpartyCollides(std::shared_ptr<Item> container)
{
    // Get Sparty's position
    double spartyX = mPlayer->GetX();
    double spartyY = mPlayer->GetY();

    // Get container's position
    double containerX = container->GetX();
    double containerY = container->GetY();

    // Define a headbutt range (adjust this value if needed)
    double headbuttRange = 1.5;

    // Check if Sparty is close enough in both X and Y directions
    return (std::abs(spartyX - containerX) <= headbuttRange &&
            std::abs(spartyY - containerY) <= headbuttRange);
}
/**
 * Starting the shift animation for the player.
 *
 * @param x the x coordinate we are at.
 * @param y the y coordinate we are at.
 */
void Game::StartShiftAnimation(wxCoord x, wxCoord y)
{

    if (mIsFrozen)
    {
        return;
    }
    mPlayer->StartHeadbuttAnimation();
    /// Handle the rest of the headbutting logic here

    for (auto& item : mItems)
    {
        ContainerOpenVisitor containerVisitor;
        item->Accept(&containerVisitor);
        if (!containerVisitor.IsOpen())
        {
            // Check if Sparty is close enough to headbutt
            if (SpartyCollides(item))
            {
                ContainerHeadButtVisitor containerHeadbutt;
                item->Accept(&containerHeadbutt);
                return;
            }
        }
    }
}

/**
 * Handle updates for animation.
 * @param elapsed The time since the last update.
 */
void Game::Update(double elapsed)
{
    // Update all items that need regular updates
    if (mPlayer != nullptr)
    {
        mPlayer->Update(elapsed);
    }
}

/**
 * Translates and scales the graphics context we are drawing on.
 *
 * @param gc The graphics context we are translating and scaling.
 */
void Game::SetScaleAndTranslation(std::shared_ptr<wxGraphicsContext> gc)
{
    gc->PushState();
    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);
}

/**
 * Solve the game by moving the correct letters to the target positions.
 */
void Game::SolveGame()
{
    for (auto item : mItems)
    {
        LetterSolverVisitor letterSolver(mAnswer);
        item->Accept(&letterSolver);
        if (letterSolver.MoveLetter())
        {
            mAnswer->Solve(item);
        }
    }
}

/**
 * Place a letter from the tray at the player's current position.
 * @param key The key code of the letter to place (A-Z or -).
 * @return Returns false only if we could not place a letter due to spot being filled.
 */
bool Game::PlaceLetter(int key)
{
    /// Get the letters in the tray
    TraysLettersVisitor traysLetters;

    for (auto item : mItems)
    {
        item->Accept(&traysLetters);
    }
    auto trayLetters = traysLetters.GetLetters();
    
    if (trayLetters.empty())
    {
        return true;  // No letters in tray
    }
    
    /// Find the letter in the tray matching the key pressed
    std::shared_ptr<Item> matchingLetter = nullptr;
    
    for (auto letter : trayLetters)
    {
        LetterVisitorValue letterVisitor;
        letter->Accept(&letterVisitor);
        int value = letterVisitor.LetterValue();

        /// Check if the value matches the key pressed
        bool isMatch = false;
        if (key >= 'A' && key <= 'Z') {
            // Convert key code to corresponding value (A→0, B→1, etc.)
            int letterValue = key - 65;

            /// Check both the exact value
            isMatch = (value == letterValue);
        } else if (key == '-') {
            isMatch = (value == -20);
        }

        if (isMatch)
        {
            matchingLetter = letter;
            break;
        }
    }
    
    if (matchingLetter == nullptr)
    {
        return true;  /// Letter not found in tray
    }
    
    /// Set the position of the letter to the player's plus the target of the player
    auto playerX = mPlayer->GetX() * TileWidth() * mScale + mXOffset;
    auto playerY = mPlayer->GetY() * TileHeight() * mScale + mYOffset;
    playerX += mPlayer->GetTargetX() * mScale;
    playerY += mPlayer->GetTargetY() * mScale;

    /// switch to screen coordinates
    double clickedSpotX = (playerX -  mXOffset) / mScale;
    double clickedSpotY = (playerY - mYOffset) / mScale;
    /// sutract by half of the letters height and width so that the letters center is at the spot clicked
    auto placedSpotX = clickedSpotX - matchingLetter->GetWidth() / 2;
    auto placedSpotY = clickedSpotY - matchingLetter->GetHeight() / 2;
    /// col row coordinates
    placedSpotX /= mTileWidth;
    placedSpotY /= mTileHeight;

    clickedSpotX /= mTileWidth;
    clickedSpotY /= mTileHeight;
    /// place the matching letter
    if (mAnswer->HitTest(clickedSpotX, clickedSpotY))
    {

        if (mAnswer->SpotFilled(matchingLetter, clickedSpotX))
        {
            /// SOME SORT OF POPUP THAT SAYS SPOT IS ALREADY TAKEN
            return false;
        }

        placedSpotX = round(placedSpotX);
        placedSpotY = round(placedSpotY);
        matchingLetter->SetLocation(placedSpotX, placedSpotY);
    }
    else
    {
        matchingLetter->SetLocation(placedSpotX, placedSpotY);
    }
    auto removed = RemoveFromTray(matchingLetter);
    if (removed)
    {
        mPlayer->StartOpenAnimation();
    }
    return true;
}

/**
 * Assign the loaded in answer to mAnswer.
 *
 * @param answer The answer to assign.
 */
void Game::AddAnswer(shared_ptr<InvisibleAnswer> answer)
{
    mAnswer = std::move(answer);
    for (auto item : mItems)
    {
        mAnswer->AddGivenToSolution(item);
    }

}

/**
 * Remove a letter from the tray.
 *
 * @param matchingLetter The letter we want to remove.
 * @return Bool if we removed a letter or not.
 */
bool Game::RemoveFromTray(std::shared_ptr<Item> matchingLetter)
{
    /// Remove the letter from the tray
    TrayRemoveLetterVisitor trayRemove(matchingLetter);
    for (auto item : mItems)
    {
        item->Accept(&trayRemove);
    }

    bool removed = trayRemove.RemovedLetter();
    if (!removed)
    {
        return false;  // Couldn't remove from tray
    }

    /// Add the letter back to the game's items list
    mItems.push_back(matchingLetter);

    return true;
}

/**
 * This function checks if the player hit an obstacle.
 *
 * @param currentXPos The x position of the player.
 * @param currentYPos The y position of the player.
 * @return bool if it was hit.
 */
bool Game::ObstacleHitTest(double currentXPos, double currentYPos)
{
    /// create a wxRect for the player object
    wxRect playerRect(currentXPos * mTileWidth, currentYPos * mTileHeight - mPlayer->GetHeight(),
        mPlayer->GetWidth(), mPlayer->GetHeight());
    ObstacleVisitorHitTest obstacleVisitor(this, playerRect);
    for (auto item : mItems)
    {
        item->Accept(&obstacleVisitor);
    }

    /// check if obstaacle was hit
    if (obstacleVisitor.WasHit())
    {
        TrayDropOneLetterVisitor dropVisitor;

        /// call visitor on every item
        for (auto& item : mItems)
        {
            item->Accept(&dropVisitor);
        }
        auto droppedLetter = dropVisitor.GetDroppedLetter();
        if (droppedLetter)
        {
            /// for random drop location on the left side of the road
            double minTileX = 0;
            double maxTileX = 3;
            double minTileY = mHeight - 8;
            double maxTileY = (double)mHeight - 1;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> xDist(minTileX, maxTileX);
            std::uniform_real_distribution<> yDist(minTileY, maxTileY);

            double randomTileX = xDist(gen);
            double randomTileY = yDist(gen);

            droppedLetter->SetLocation(randomTileX, randomTileY);

            mItems.push_back(droppedLetter);
        }
        return true;
    }
    return false;
}

/**
 * Cache a picture either finds the picture or creates one.
 *
 * @param name The image name.
 * @return A shared pointer to the picture.
 */
std::shared_ptr<Picture> Game::GetCachedPicture(const std::wstring name)
{
    auto i = mCachedPictures.find(name);
    if (i != mCachedPictures.end())
    {
        return i->second;
    }
    auto new_picture = std::make_shared<Picture>(name);
    mCachedPictures[name] = new_picture;
    return new_picture;
}