/**
 * @file LetterCoordVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "LetterCoordVisitor.h"
#include "Letter.h"

/**
 * Visit the letters and record their x and y tray coordinates.
 *
 * @param letter The letter we are visiting.
 */
void LetterCoordVisitor::VisitLetter(Letter* letter)
{
    mX = letter->GetTrayX();
    mY = letter->GetTrayY();
}