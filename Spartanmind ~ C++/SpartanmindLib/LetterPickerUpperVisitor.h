/**
 * @file LetterPickerUpperVisitor.h
 * @author Jackson White
 *
 * This is a visitor that picks up the letter if it was clicked.
 */
 
#ifndef LETTERPICKERUPPERVISITOR_H
#define LETTERPICKERUPPERVISITOR_H

#include "ItemVisitor.h"

/**
 * Letter picker upper class.
 *
 * Hit tests the letter and checks if it was picked up.
 */
class LetterPickerUpperVisitor : public ItemVisitor {
private:
    /// If the letter is going to be picked up or not.
    bool mPickedUp = false;
    /// X position.
    double mYPos;
    /// Y position.
    double mXPos;

public:
    /**
     * Constructor of the LetterPickerUpperVisitor.
     *
     * @param x The x position to hitcheck
     * @param y The y position to hitcheck
     */
    LetterPickerUpperVisitor(double x, double y) : mXPos(x), mYPos(y) {};
    void VisitLetter(Letter* letter) override;

    /**
     * Returns mPickedUp.
     * @return If the letter was picked up or not.
     */
    bool PickedUpLetter() {return mPickedUp;}
};

#endif //LETTERPICKERUPPERVISITOR_H