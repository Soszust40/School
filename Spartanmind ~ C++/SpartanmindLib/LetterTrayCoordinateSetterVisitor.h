/**
 * @file LetterTrayCoordinateSetterVisitor.h
 * @author Jackson White
 *
 * Visitor that only visits letters and sets the letter to specific tray coordinates.
 */
 
#ifndef LETTERTRAYCOORDINATESETTER_H
#define LETTERTRAYCOORDINATESETTER_H

#include "ItemVisitor.h"

/**
 * LetterVisitor derived from Item Visitor.
 *
 * Visits the letter and sets its tray coordinates.
 */
class LetterTrayCoordinateSetterVisitor : public ItemVisitor{
private:
    /// The X tray coordinate.
    double mTrayX;

    /// The Y tray coordinate.
    double mTrayY;
public:
    /**
     * Custom constructor that sets mTrayX and mTrayY.
     *
     * @param trayX The tray X location.
     * @param trayY The tray Y location.
     */
    LetterTrayCoordinateSetterVisitor(double trayX, double trayY) {mTrayX = trayX; mTrayY = trayY;};

    void VisitLetter(Letter* letter) override;
};

#endif //LETTERTRAYCOORDINATESETTER_H
