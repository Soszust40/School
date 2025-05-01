/**
 * @file LetterInTrayDrawer.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "LetterInTrayDrawer.h"
#include "Letter.h"

/**
 * Overriden visitor function that visits letters and draws them in the tray.
 *
 * @param letter The letter we are visiting.
 */
void LetterInTrayDrawer::VisitLetter(Letter* letter)
{
    letter->DrawInTray(mGraphics);
}
