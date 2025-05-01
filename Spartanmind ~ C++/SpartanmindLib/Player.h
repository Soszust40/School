/**
 * @file Player.h
 * @author Noah Patenaude
 *
 * Class that describes a Player.
 */
 
#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"

/**
 * Class that describes a Player.
 */
class Player : public Item {
public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPlayer(this); }

    void OnLeftDown(double screenX, double screenY) override;

    /// Player type
    enum class Type {Car, Sparty, Chest};

    /// Default constructor (disabled)
    Player() = delete;

    /// Copy constructor (disabled)
    Player(const Player &) = delete;

    Player(Game* game, int level, const std::wstring& image1name, const std::wstring& image2name);

    /// Assignment operator
    void operator=(const Player &) = delete;

    void SetType(Type type);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Starts the player opening animation to set mIsOpen to true.
     */
    void StartOpenAnimation();

    /**
     * Starts the player headbutt animation to get mIsHeadbutt to true.
     */
    void StartHeadbuttAnimation();

    void Update(double elapsed) override;

    void XmlLoad(wxXmlNode* node, wxXmlNode* declaration) override;

    /**
     * Gets the TargetX which the player is shifted by.
     *
     * @return Int of the targetX.
     */
    int GetTargetX() {return mTargetX;}

    /**
     * Gets the TargetY which the player is shifted.
     *
     * @return Int of the targetY.
     */
    int GetTargetY() {return mTargetY;}

private:
    /// the original x position of the player
    double mOrigX;
    /// the original y position of the player
    double mOrigY;
    /// Add these variables for smooth movement
    double mTargetXPos = 0;    ///< Target X position for smooth movement
    double mTargetYPos = 0;    ///< Target Y position for smooth movement
    bool mIsMoving = false;    ///< Whether the player is currently moving
    double mCurrentXPos = 0;   ///< Current X position
    double mCurrentYPos = 0;   ///< Current Y position

    /// Timer used for tracking animation progress
    double mAnimationTime = 0.0;

    /// The current angle of the open
    double mCurrentAngle = 0;
    /// The current angle of Player Body
    double mCurrentBodyAngle = 0;
    /// The point for headbutt animation
    wxPoint mAuxPointHeadButt;
    /// The point for spacebar animation
    wxPoint mAuxPointSpaceBar;

    /// Dictates which image is drawn first.
    /// A value of 1 means that Image 1 should be in front
    int mFront;
    /// The angle the head pivits
    double mPivotAngle1;
    /// The angle the mouth pivits
    double mPivotAngle2;
    /// The target in the x direction
    int mTargetX;
    /// The target in the y diretion
    int mTargetY;
    /// The current level the player is in
    int mLevel;
    /// What type the player is : defaults to chest
    Type mType;
    /// First image for the player
    std::shared_ptr<wxImage> mFirstImage = nullptr;
    /// First bitmap we can display
    std::shared_ptr<wxBitmap> mFirstBitmap = nullptr;
    /// Second image for the player (mouth for Sparty, lid for Chest)
    std::shared_ptr<wxImage> mSecondImage = nullptr;
    /// Second bitmap we can display
    std::shared_ptr<wxBitmap> mSecondBitmap = nullptr;

    /// boolean if the spacebar was hit, and we are opening/closing animation
    bool mIsOpen = false;

    /// boolean if the spacebar was hit, and we are opening/closing animation
    bool mClosing = false;

    /// boolean if the shift button was hit then we are playing the headbutt animation
    bool mIsHeadbutting = false;

    bool HitTest(double x, double y) override;
};

#endif //PLAYER_H
