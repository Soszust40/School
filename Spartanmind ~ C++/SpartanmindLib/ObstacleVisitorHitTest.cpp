/**
 * @file ObstacleVisitorHitTest.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "ObstacleVisitorHitTest.h"
#include "Game.h"

/**
 * Override obstacle visit function that hittests the obstacle.
 * @param obstacle The obstacle we are visiting.
 */
void ObstacleVisitorHitTest::VisitObstacle(Obstacle* obstacle)
{
    auto width = obstacle->GetWidth();
    auto height = obstacle->GetHeight();
    auto gamewidth = mGame->GetWidth();
    auto gameheight = mGame->GetHeight();

    wxRect obstacleRect(obstacle->GetX() * mGame->TileWidth() + 10, obstacle->GetY() * mGame->TileHeight() - obstacle->GetHeight(), obstacle->GetWidth() -35, obstacle->GetHeight());
    if (mPlayerRect.Intersects(obstacleRect))
    {
        mHit = true;
    }
}
