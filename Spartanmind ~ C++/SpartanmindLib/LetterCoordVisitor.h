/**
 * @file LetterCoordVisitor.h
 * @author Jackson White
 *
 * Visitor to get the coords of the letters in the tray.
 */
 
#ifndef LETTERCOORDVISITOR_H
#define LETTERCOORDVISITOR_H

#include "ItemVisitor.h"

/**
 * Letter visitor, derived from ItemVisitor.
 *
 * Returns the letters xTray and yTray coordinates.
 */
class LetterCoordVisitor : public ItemVisitor {
private:
    /// The X coordinate
    double mX;
    /// The Y coordinate
    double mY;
public:
    void VisitLetter(Letter* letter) override;

    /**
     * Get the location of the letter in the tray.
     *
     * @return The X location in the tray.
     */
    double GetX() {return mX; };

    /**
     * Get the location of the letter in the tray.
     *
     * @return The Y location in the tray.
     */
    double GetY() {return mY; };
};

#endif //LETTERCOORDVISITOR_H
