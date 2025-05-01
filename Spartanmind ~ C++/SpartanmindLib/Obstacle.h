/**
 * @file Obstacle.h
 * @author Jackson White
 * @author Simon Oszust
 */
 
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Item.h"

/**
 * Obstacle class derived from item
 */
class Obstacle : public Item {
private:

public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitObstacle(this); }

    /**
     * Default constructor (disabled)
     */
    Obstacle() = delete;

    /**
    * Copy constructor (disabled)
    */
    Obstacle(const Obstacle &) = delete;

    /**
     * Assignment operator (disabled)
     */
    void operator=(const Obstacle &) = delete;

    Obstacle(Game *game, const std::wstring &imageName);

    /// Handle loading from XML
    void XmlLoad(wxXmlNode *node, wxXmlNode *declaration) override;
    bool PlayerCollisionTest(double x, double y);
};

#endif //OBSTACLE_H
