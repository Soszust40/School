/**
 * @file LetterTrayCoordinateSetterVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "LetterTrayCoordinateSetterVisitor.h"
#include "Letter.h"

/**
 * Overriden VisitLetter function that will set the tray coordinates of a letter.
 *
 * @param letter The letter we are visiting.
 */
void LetterTrayCoordinateSetterVisitor::VisitLetter(Letter* letter)
{
    letter->SetTrayCoordinate(mTrayX, mTrayY);
}
