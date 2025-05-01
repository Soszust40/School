/**
 * @file Player.cpp
 * @author Noah Patenaude
 * @author Simon Oszust
 */

#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Picture.h"
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

/// Player character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for a grabbing cycle in seconds
const double GrabbingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/// Sparty top image
const std::wstring spartyImageName = L"images/sparty.png";
/// Sparty mouth image
const std::wstring spartyMouthImageName = L"images/sparty-mouth.png";
/// Chest bottom image
const std::wstring chestImageName = L"images/chest.png";
/// Chest top image
const std::wstring chestLidImageName = L"images/chest-lid.png";

/**
 * Constructor for player.
 * @param game The game object.
 * @param level The current level that the game is on.
 * @param image1name The main image for the player.
 * @param image2name The animated image for the player.
 */
Player::Player(Game *game, int level, const std::wstring &image1name, const std::wstring& image2name)
    : Item(game, L"")
{
    auto picture1 = GetGame()->GetCachedPicture(image1name);
    auto picture2 = GetGame()->GetCachedPicture(image2name);
    mFirstImage = picture1->GetImage();
    mSecondImage = picture2->GetImage();
    mFirstBitmap = picture1->GetBitmap();
    mSecondBitmap = picture2->GetBitmap();

    mLevel = level;
    if (mLevel == 3)
    {
        mType = Type::Car;
    }
    else if (mLevel == 2)
    {
        mType = Type::Sparty;
    }
    else
    {
        mType = Type::Chest;
    }
}
/**
 * Sets the type of player.
 * @param type The type to set player to.
 */
void Player::SetType(Type type)
{
    mType = type;
}

/**
 * Draw the player based upon what mType is.
 * @param graphics Graphics context to draw on.
 */
void Player::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mFirstBitmap->IsNull())
    {
        mFirstBitmap = make_shared<wxBitmap>(*mFirstImage);
    }

    if (mSecondBitmap->IsNull())
    {
        mSecondBitmap = make_shared<wxBitmap>(*mSecondImage);
    }
    
    if (mIsOpen)
    {
        int pixelWidth = GetWidth();
        int pixelHeight = GetHeight();
        
        // Get the dimensions for the second image (mouth/lid)
        int secondWidth = mSecondImage->GetWidth();
        int secondHeight = mSecondImage->GetHeight();
        
        if (mFront == 1)
        {
            // For Sparty, draw the mouth UNDER the head
            
            // First draw the mouth with rotation (second image)
            graphics->PushState();
            graphics->Translate(GetX() * GetGame()->TileWidth(), (GetY() - 1) * GetGame()->TileHeight());
            
            // Get pivot point for rotation
            auto pivotX = mAuxPointSpaceBar.x;
            auto pivotY = mAuxPointSpaceBar.y;
            
            // Apply rotation around pivot point
            graphics->Translate(pivotX, pivotY);
            graphics->Rotate(mCurrentAngle);
            graphics->Translate(-pivotX, -pivotY);
            
            // Draw the mouth with correct dimensions
            graphics->DrawBitmap(*mSecondBitmap, 0, 0, secondWidth, secondHeight);
            graphics->PopState();
            
            // Then draw the head (first image) on top
            graphics->PushState();
            auto headX = GetX() * GetGame()->TileHeight();
            auto headY = (GetY() + 1) * GetGame()->TileWidth() - pixelHeight;
            graphics->Translate(headX, headY);
            graphics->DrawBitmap(*mFirstBitmap, 0, 0, pixelWidth, pixelHeight);
            graphics->PopState();
        }
        else if (mFront == 2)
        {
            graphics->PushState();
            auto baseX = GetX() * GetGame()->TileHeight();
            auto baseY = (GetY() + 1) * GetGame()->TileWidth() - pixelHeight;
            graphics->Translate(baseX, baseY);
            graphics->DrawBitmap(*mFirstBitmap, 0, 0, pixelWidth, pixelHeight);
            graphics->PopState();

            // Step 2: Draw the lid with rotation (background)
            graphics->PushState();
            graphics->Translate(GetX() * GetGame()->TileWidth(), (GetY() - 1) * GetGame()->TileHeight());

            // Get pivot point for rotation
            auto pivotX = mAuxPointSpaceBar.x;
            auto pivotY = mAuxPointSpaceBar.y;

            // Apply rotation around pivot point
            graphics->Translate(pivotX, pivotY);
            graphics->Rotate(mCurrentAngle);
            graphics->Translate(-pivotX, -pivotY);

            // Draw the lid with correct dimensions
            graphics->DrawBitmap(*mSecondBitmap, 0, 0, secondWidth, secondHeight);
            graphics->PopState();
        }
    }
    else if (mIsHeadbutting)
    {
        int pixelWidth = GetWidth();
        int pixelHeight = GetHeight();

        graphics->PushState();

        // Move to player's current position
        double newX = GetX() * GetGame()->TileWidth();
        double newY = (GetY() + 1) * GetGame()->TileHeight() - pixelHeight;

        graphics->Translate(newX, newY);

        // Move origin to the headbutt pivot point
        graphics->Translate(mAuxPointHeadButt.x, mAuxPointHeadButt.y);

        // Apply rotation
        graphics->Rotate(mCurrentAngle);

        // Move back
        graphics->Translate(-mAuxPointHeadButt.x, -mAuxPointHeadButt.y);

        // Draw player image at (0,0) since transformations handle positioning
        graphics->DrawBitmap(*mSecondBitmap, 0, 0, pixelWidth, pixelHeight);
        graphics->DrawBitmap(*mFirstBitmap, 0, 0, pixelWidth, pixelHeight);

        graphics->PopState();
    }
    else
    {
        int pixelWidth = GetWidth();
        int pixelHeight = GetHeight();
        
        // Get dimensions for the second image
        int secondWidth = mSecondImage->GetWidth();
        int secondHeight = mSecondImage->GetHeight();
        
        if (mFront == 1)
        {
            // For Sparty, draw the mouth first (under the head)
            graphics->PushState();
            graphics->Translate(GetX() * GetGame()->TileWidth(), (GetY() - 1) * GetGame()->TileHeight());
            graphics->DrawBitmap(*mSecondBitmap, 0, 0, secondWidth, secondHeight);
            graphics->PopState();
            
            // Then draw the head (on top)
            graphics->PushState();
            graphics->DrawBitmap(*mFirstBitmap, GetX() * GetGame()->TileHeight(), (GetY() + 1) * GetGame()->TileWidth() - pixelHeight, pixelWidth, pixelHeight);
            graphics->PopState();
        }
        else if (mFront == 2)
        {
            // For chest, draw in the original order
            graphics->PushState();
            graphics->DrawBitmap(*mFirstBitmap,GetX() * GetGame()->TileHeight(), (GetY() + 1) * GetGame()->TileWidth() - pixelHeight, pixelWidth, pixelHeight);
            graphics->PopState();

            graphics->PushState();
            graphics->Translate(GetX() * GetGame()->TileWidth(), (GetY() - 1) * GetGame()->TileHeight());
            graphics->DrawBitmap(*mSecondBitmap, 0, 0, secondWidth, secondHeight);
            graphics->PopState();
        }
    }
}

/**
 * HitText for the player to check clicks.
 * @param x X location in pixels.
 * @param y Y location in pixels.
 * @return bool of if the click was inside the image or not.
 */
bool Player::HitTest(double x, double y)
{
    int pixelHeight = GetHeight();

    auto spotX = GetX();
    auto spotY = GetY();

    spotX *= 48;
    spotY = (spotY+1) * 48 - pixelHeight;

    /// Make x and y relative to the top-left corner of the bitmap
    spotX = x - spotX + (GetWidth() / 2);
    spotY = y - spotY + (GetHeight() / 2);

    /// Test to see if x, y are in the image
    if (spotX < 0 || spotY < 0 || spotX >= GetWidth() || spotY >= GetHeight())
    {
        // Outside the image
        return false;
    }
    bool check =  !mFirstImage->IsTransparent((int)spotX, (int)spotY);
    if (check)
    {
        return true;
    }
    pixelHeight = GetHeight();

    spotX = GetX();
    spotY = GetY();

    spotX *= 48;
    spotY = (spotY+1) * 48 - pixelHeight;

    /// Make x and y relative to the top-left corner of the bitmap
    spotX = x - spotX + (GetWidth() / 2);
    spotY = y - spotY + (GetHeight() / 2);

    /// Test to see if x, y are in the image
    if (spotX < 0 || spotY < 0 || spotX >= GetWidth() || spotY >= GetHeight())
    {
        // Outside the image
        return false;
    }
    return !mSecondImage->IsTransparent((int)spotX, (int)spotY);
}

/**
 * Load the player in.
 *
 * @param node Item node.
 * @param declaration Declaration nodes.
 */
void Player::XmlLoad(wxXmlNode* node, wxXmlNode* declaration)
{
    Item::XmlLoad(node, declaration);

    declaration->GetAttribute(L"front", L"0").ToInt(&mFront);
    declaration->GetAttribute(L"head-pivot-angle", L"0").ToDouble(&mPivotAngle1);
    declaration->GetAttribute(L"head-pivot-x", L"0").ToInt(&mAuxPointHeadButt.x);
    declaration->GetAttribute(L"head-pivot-y", L"0").ToInt(&mAuxPointHeadButt.y);

    declaration->GetAttribute(L"mouth-pivot-angle", L"0").ToDouble(&mPivotAngle2);
    declaration->GetAttribute(L"mouth-pivot-x", L"0").ToInt(&mAuxPointSpaceBar.x);
    declaration->GetAttribute(L"mouth-pivot-y", L"0").ToInt(&mAuxPointSpaceBar.y);

    declaration->GetAttribute(L"target-x", L"0").ToInt(&mTargetX);
    declaration->GetAttribute(L"target-y", L"0").ToInt(&mTargetY);

    node->GetAttribute(L"col", L"0").ToDouble(&mOrigX);
    node->GetAttribute(L"row", L"0").ToDouble(&mOrigY);
}

/**
 * Move the player when left-clicked
 * @param oX X coordinate
 * @param oY Y coordinate
 */
void Player::OnLeftDown(double oX, double oY)
{
    /// X location needs to be in the center of the player, so divide by half the width and subtract from X
    oX -= mTargetX;
    oY -= mTargetY;
    /// will need to change this to tile height once we load it in
    oX /= GetGame()->TileWidth();
    oY /= GetGame()->TileHeight();
    
    /// Set the target position for smooth movement
    mTargetXPos = oX;
    mTargetYPos = oY;
    
    /// Initialize current position if not moving yet
    if (!mIsMoving) {
        mCurrentXPos = GetX();
        mCurrentYPos = GetY();
    }
    
    /// Start moving to the new target
    mIsMoving = true;
}

/**
 * The player will start the opening animation when spacebar is hit.
 */
void Player::StartOpenAnimation()
{
    mIsOpen = true;
    mClosing = false;
    mCurrentAngle = 0.0;
    mAnimationTime = 0.0; // Initialize animation timer
}

void Player::StartHeadbuttAnimation()
{
    mIsHeadbutting = true;
    mCurrentAngle = 0.0;
}

/**
 * Handle updates for animation and movement.
 * @param elapsed The time since the last update.
 */
void Player::Update(double elapsed)
{
    // Handle animation for opening/closing
    if (mIsOpen)
    {
        // Increment the animation timer
        mAnimationTime += elapsed;
        
        if (!mClosing)
        {
            // Opening phase (first half of animation)
            if (mAnimationTime <= GrabbingTime / 2)
            {
                // Linear interpolation from 0 to pivot angle
                double t = mAnimationTime / (GrabbingTime / 2); // t goes from 0 to 1
                mCurrentAngle = mType == Type::Sparty ? mPivotAngle2 * t : mPivotAngle1 * t;
            }
            else
            {
                // Opening phase complete, switch to closing
                mCurrentAngle = mType == Type::Sparty ? mPivotAngle2 : mPivotAngle1;
                mClosing = true;
            }
        }
        else
        {
            // Closing phase (second half of animation)
            double closingTime = mAnimationTime - (GrabbingTime / 2);
            
            if (closingTime <= GrabbingTime / 2)
            {
                // Linear interpolation from pivot angle to 0
                double t = closingTime / (GrabbingTime / 2); // t goes from 0 to 1
                double maxAngle = mType == Type::Sparty ? mPivotAngle2 : mPivotAngle1;
                mCurrentAngle = maxAngle * (1.0 - t);
            }
            else
            {
                // Animation complete
                mCurrentAngle = 0.0;
                mClosing = false;
                mIsOpen = false;
            }
        }

    }

    /// Handle animation for the headbutt
    if (mIsHeadbutting)
    {
        double changeHeadbutt = HeadbuttTime + elapsed;

        if (!mClosing) // Rotating forward
        {
            mCurrentAngle += changeHeadbutt;
            if (mCurrentAngle >= mPivotAngle1) // Forward rotation complete
            {
                mCurrentAngle = mPivotAngle1;
                mClosing = true; // Start rotating back
            }
        }
        else // Rotating back
        {
            mCurrentAngle -= changeHeadbutt;
            if (mCurrentAngle <= 0) // Back to normal
            {
                mCurrentAngle = 0;
                mClosing = false;
                mIsHeadbutting = false; // Animation ends
            }
        }
    }
    
    // Handle smooth movement to target location
    if (mIsMoving) {
        // Calculate distance to target
        double dx = mTargetXPos - mCurrentXPos;
        double dy = mTargetYPos - mCurrentYPos;
        double distance = sqrt(dx*dx + dy*dy);
        
        // Use a larger threshold to prevent oscillation
        if (distance < 0.1) {  // Increased from 0.05 to 0.1
            // If very close, just snap to the exact position
            mCurrentXPos = mTargetXPos;
            mCurrentYPos = mTargetYPos;
            mIsMoving = false;
            if (GetGame()->ObstacleHitTest(mCurrentXPos, mCurrentYPos))
            {
                mCurrentXPos = mOrigX;
                mCurrentYPos = mOrigY;
                mIsMoving = false;
                
                // Signal that an obstacle was hit
                GetGame()->SetObstacleHit(true);
            }
            // Update actual position
            SetLocation(mCurrentXPos, mCurrentYPos);
            return;
        }
        
        // Calculate movement this frame
        double moveDistance = MaxSpeed * elapsed / 48.0; // Convert pixels/sec to tiles/sec
        
        // Limit movement to the remaining distance to prevent overshooting
        if (moveDistance > distance) {
            moveDistance = distance;
        }
        
        // Normalize direction vector
        double moveX = dx / distance;
        double moveY = dy / distance;
        
        // Calculate new position
        auto newSpotX = mCurrentXPos + moveX * moveDistance;
        auto newSpotY = mCurrentYPos + moveY * moveDistance;

        auto scale = GetGame()->GetScale();
        auto virtualGameWidth = GetGame()->GetWidth();
        auto virtualGameHeight = GetGame()->GetHeight();

        auto objectVirtualWidth  = ((GetWidth())/ GetGame()->TileWidth()) * scale;
        //auto objectVirtualHeight = ((GetHeight() - mTargetY)/ GetGame()->TileHeight()) * scale;
        auto objectVirtualHeight = ((GetHeight() - mTargetY)/ GetGame()->TileHeight()) * scale;


        if (newSpotX <= 0)
        {
            newSpotX = 0;
        }
        else if (newSpotX + objectVirtualWidth > virtualGameWidth)
        {
            newSpotX = GetGame()->GetWidth() - (GetWidth() / GetGame()->TileWidth());
        }
        if (newSpotY < 0 )
        {
            newSpotY = 0;
        }
        else if (newSpotY >= virtualGameHeight)
        {
            newSpotY = virtualGameHeight;
        }
        if ((newSpotY - objectVirtualHeight <= 0 || newSpotY >= virtualGameHeight) && (newSpotX <= 0 || newSpotX + objectVirtualWidth >= virtualGameWidth))
        {
            mIsMoving = false;
            return;
        }
        //mCurrentXPos += moveX * moveDistance;
        //mCurrentYPos += moveY * moveDistance;
        mCurrentXPos = newSpotX;
        mCurrentYPos = newSpotY;

        if (GetGame()->ObstacleHitTest(mCurrentXPos, mCurrentYPos))
        {
            mCurrentXPos = mOrigX;
            mCurrentYPos = mOrigY;
            mIsMoving = false;
            
            // Signal that an obstacle was hit
            GetGame()->SetObstacleHit(true);
        }
        // Update actual position
        SetLocation(mCurrentXPos, mCurrentYPos);
    }
}