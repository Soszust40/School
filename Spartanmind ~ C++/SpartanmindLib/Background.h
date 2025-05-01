/**
 * @file Background.h
 * @author Jackson White
 *
 * The background of our class, derived from item
 */

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Item.h"

/**
 * Background class for our background.
 */
class Background : public Item {

public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBackground(this); }
    Background(Game* game, const std::wstring& imageName);

    /// Default constructor (disabled)
    Background() = delete;

    /// Copy constructor (disabled)
    Background(const Background &) = delete;

    /// Assignment operator
    void operator=(const Background &) = delete;
};

#endif //BACKGROUND_H
