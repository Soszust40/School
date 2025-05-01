/**
 * @file Obstacle.cpp
 * @author Jackson White
 * @author Simon Oszust
 */

#include "pch.h"
#include "Obstacle.h"
#include "Game.h"

/**
 * Constructor for an Obstacle.
 * @param game The game instance.
 * @param imageName The image file path for the obstacle.
 */
Obstacle::Obstacle(Game *game, const std::wstring &imageName)
    : Item(game, imageName) {
}

/**
 * Load the obstacle from XML data.
 * @param node XML node with obstacle data.
 * @param declaration XML declaration node.
 */
void Obstacle::XmlLoad(wxXmlNode *node, wxXmlNode *declaration)
{
    Item::XmlLoad(node, declaration);
}

/**
 * This function checks if the player has collided with the obstacle.
 *
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @return True if we have hit the obstacle.
 */
bool Obstacle::PlayerCollisionTest(double x,double y)
{
    double obstacleX = GetX();
    double obstacleY = GetY();
    double width = GetWidth();
    double height = GetHeight();
    if (obstacleX <= x && x <= obstacleX + width && obstacleY <= y && y <= obstacleY + height)
    {
        return true;
    }
    return false;
}