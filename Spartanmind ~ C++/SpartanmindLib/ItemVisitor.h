/**
 * @file ItemVisitor.h
 * @author Jackson White
 *
 * Item visitor base class
 */

#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

class Given;
class Letter;
class Player;
class Tray;
class Background;
class Container;
class Obstacle;

/**
 * Item visitor base class.
 */
class ItemVisitor {
protected:
    /**
     * Constructor for the Item Visitor Class.
     * Ensures this is an abstract class.
     */
    ItemVisitor() {}
private:

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit the player.
     * @param player Player item we are visiting.
     */
    virtual void VisitPlayer(Player* player) {}

    /**
     * Visit the obstacle.
     * @param obstacle Item we are visiting.
     */
    virtual void VisitObstacle(Obstacle* obstacle) {}

    /**
     * Visit the Letter.
     * @param letter Player item we are visiting.
     */
    virtual void VisitLetter(Letter* letter) {}

    /**
     * Visit the given.
     * @param given Player item we are visiting.
     */
    virtual void VisitGiven(Given* given) {}

    /**
     * Visit the Background.
     * @param background Player item we are visiting.
     */
    virtual void VisitBackground(Background* background) {}

    /**
     * Visit the Tray.
     * @param tray Player item we are visiting.
     */
    virtual void VisitTray(Tray* tray) {}

    /**
     * Visit the Container.
     * @param container Player item we are visiting.
     */
    virtual void VisitContainer(Container * container) {}
};

#endif //ITEMVISITOR_H
