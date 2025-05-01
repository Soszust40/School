/**
 * @file Game.h
 * @author Jackson White
 * @author Aditya Menon
 * @author Simon Oszust
 *
 * The class that holds our Game object.
 */
 
#ifndef GAME_H
#define GAME_H

class Item;
class Player;
class Background;
class Tray;
class Container;
class Picture;

#include "InvisibleAnswer.h"
#include "Loader.h"
#include <memory>

/**
 * Game class that is our game object.
 */
class Game {
private:
    /// Cache of pictures
    std::map<std::wstring, std::shared_ptr<Picture>> mCachedPictures;
    /// Is the game frozen
    bool mIsFrozen = false;
    /// The current level we are on
    int mLevel;
    /// The loader for the game. It will load levels
    std::unique_ptr<Loader> mLoader = nullptr;
    /// The answer to the game
    std::shared_ptr<InvisibleAnswer> mAnswer = nullptr;
    /// The scale of which we are adjusting the size of the background
    double mScale = 1.1138888888888889; //<< this value gets overriden whenever we load. Set to this for loading purposes
    /// Offset in the X direction
    double mXOffset = 57.333333333333258; //<< this value gets overriden whenever we load. Set to this for loading purposes
    /// Offset in the y direction
    double mYOffset = 0;

    /// All of the items to populate our game.
    std::vector<std::shared_ptr<Item>> mItems;
    /// A pointer to the player.
    std::shared_ptr<Player> mPlayer = nullptr;

    /// Gamewidth
    int mWidth;
    /// Game height
    int mHeight;
    /// Tile Width
    int mTileWidth = 48;
    /// Tile height
    int mTileHeight = 48;
    /// Flag to indicate if an obstacle was hit
    bool mObstacleHit = false;

public:
    /**
     * Destructor
    */
    virtual ~Game() = default;
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void OnLeftDown(wxCoord screenX, wxCoord screenY);
    Game();
    virtual void Clear();
    virtual void AddItem(std::shared_ptr<Item> item);
    virtual void AddPlayer(std::shared_ptr<Player> player);
    void OnLoadLevel(const std::wstring& filename);
    void XmlGame(wxXmlNode* level);
    std::shared_ptr<Item> HitTest(int x, int y);
    bool StartSpaceAnimation();
    void StartShiftAnimation(wxCoord x, wxCoord y);
    bool PlaceLetter(int key);
    virtual void AddAnswer(std::shared_ptr<InvisibleAnswer> answer);
    bool RemoveFromTray(std::shared_ptr<Item> matchingLetter);
    bool ObstacleHitTest(double currentXPos, double currentYPos);
    std::shared_ptr<Picture> GetCachedPicture(std::wstring name);
    void Update(double elapsed);
    void SetScaleAndTranslation(std::shared_ptr<wxGraphicsContext> gc);
    void SolveGame();
    bool SpartyCollides(std::shared_ptr<Item> container);

    /**
     * Check if the game is complete.
     *
     * @return True if the game is complete, false otherwise.
     */
    bool GameIsComplete() { return mAnswer->IsComplete(); }

    /**
     * Check if the game slots are fully filled.
     *
     * @return True if the game is filled out, false otherwise.
     */
    bool IsFilledOut() { return mAnswer->FilledOut(); }

    /**
     * Get the numnber of letters in the right spot.
     *
     * @return The number of correct letters.
     */
    int GetCorrectLetters() {return mAnswer->CorrectLetters(); }

    /**
     * Get the number of letters in the wrong spot.
     *
     * @return The amount of letters in the wrong spot.
     */
    int WrongSpot() {return mAnswer->WrongSpot(); }

    /**
     * Get the height of the game area in pixels.
     *
     * @return Height in pixels.
     */
    int GetHeight() const { return mHeight; }

    /**
     * Get the width of the game area in pixels.
     *
     * @return Width in pixels.
     */
    int GetWidth() const { return mWidth; }

    /**
     * Get the player pointer.
     *
     * @return Player pointer.
     */
    std::shared_ptr<Player> GetPlayer() { return mPlayer; }

    /**
     * Get the current level we are on.
     *
     * @return The integer of the level we are on.
     */
    int Level() { return mLevel; }

    /**
     * The height of the tile.
     *
     * @return Int tile height.
     */
    int TileHeight() { return mTileHeight; }

    /**
     * The width of the tile.
     *
     * @return Int tile width.
     */
    int TileWidth() { return mTileWidth; }

    /**
     * The scale of the tile.
     *
     * @return Int tile scale.
     */
    double GetScale() { return mScale; }

    /**
     * The offset in X of the tile.
     *
     * @return Int X offset.
     */
    double GetOffsetX() {return mXOffset;}

    /**
     * The offset in Y of the tile.
     *
     * @return Int Y offset.
     */
    double GetOffsetY() {return mYOffset;}

    /**
     * Freeze/Unfreeze the game.
     *
     * @param frozen Switch it to this boolean.
     */
    void SetFrozen(bool frozen) { mIsFrozen = frozen; }

    /**
     * This function checks if the game is frozen.
     *
     * @return Bool if the game is frozen.
     */
    bool IsFrozen() { return mIsFrozen; }

    /**
    * Get the number of items in the game (for test cases).
    *
    * @return The count of items in the item vector.
    */
    int GetItemsCount() const { return mItems.size(); }

    /**
     * Set the obstacle hit flag.
     * @param hit Whether an obstacle was hit
     */
    void SetObstacleHit(bool hit) { mObstacleHit = hit; }
    
    /**
     * Get the obstacle hit flag.
     * @return True if an obstacle was hit, false otherwise
     */
    bool WasObstacleHit() const { return mObstacleHit; }
};

#endif //GAME_H