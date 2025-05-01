/**
 * @file ObstacleVisitorHitTest.h
 * @author Jackson White
 *
 * Obstacle visitor that hit tests the obstacle.
 */
 
#ifndef OBSTACLEVISITORHITTEST_H
#define OBSTACLEVISITORHITTEST_H

#include "Obstacle.h"

/**
 * Obstacle visitor derived from ItemVisitor class.
 * it visits each obstacle and hit tests it.
 */
class ObstacleVisitorHitTest : public ItemVisitor {
private:
    /// The players rectangle
    wxRect mPlayerRect;
    /// The game object
    Game* mGame = nullptr;
    /// Bool if the obstacle was hit. Initially false
    bool mHit = false;
public:

    /**
     * Custom Constructor
     *
     * @param game The game object.
     * @param playerRect The players hitbox.
     */
    ObstacleVisitorHitTest(Game * game, wxRect playerRect) : mGame(game), mPlayerRect(playerRect) {}

    void VisitObstacle(Obstacle* obstacle) override;

    /**
     * Get the information of if the obstacle was hit.
     * @return True if the player hit obstacle, otherwise false.
     */
    bool WasHit() {return mHit;}
};

#endif //OBSTACLEVISITORHITTEST_H
