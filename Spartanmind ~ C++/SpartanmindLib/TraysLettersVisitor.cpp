/**
 * @file TraysLettersVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "TraysLettersVisitor.h"
#include "Tray.h"

/**
 * This function will be called on the tray we are visiting.
 * We set mLetters to the contents of the tray Letters.
 *
 * @param tray The tray we are visiting.
 */
void TraysLettersVisitor::VisitTray(Tray* tray)
{
    mLetters = tray->GetLetters();
}
