/**
 * @file LetterPickerUpperVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "LetterPickerUpperVisitor.h"
#include "Letter.h"

/**
 * Visit the letter using a visitor. This function will call hittest of the letter.
 *
 * @param letter The letter to hittest.
 */
void LetterPickerUpperVisitor::VisitLetter(Letter *letter)
{
    mPickedUp = letter->HitTest(mXPos, mYPos);
}