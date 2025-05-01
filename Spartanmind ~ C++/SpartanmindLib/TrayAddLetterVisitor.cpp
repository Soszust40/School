/**
 * @file TrayAddLetterVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "TrayAddLetterVisitor.h"
#include "Tray.h"

/**
 * Overriden visit tray function.
 *
 * This function calls AddLetter to tray and sets that value to mAddedLetter.
 * @param tray The tray object.
 */
void TrayAddLetterVisitor::VisitTray(Tray * tray)
{
    mAddedLetter = tray->AddLetter(mLetter);
}