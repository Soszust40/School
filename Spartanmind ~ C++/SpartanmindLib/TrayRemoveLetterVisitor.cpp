/**
 * @file TrayRemoveLetterVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "TrayRemoveLetterVisitor.h"
#include "Tray.h"

/**
 * Visit the tray and remove the item.
 * @param tray The tray item.
 */
void TrayRemoveLetterVisitor::VisitTray(Tray* tray)
{
    mRemovedLetter = tray->RemoveLetter(mLetter);
}