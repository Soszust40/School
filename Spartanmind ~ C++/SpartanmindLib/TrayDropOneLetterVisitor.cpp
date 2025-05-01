/**
 * @file TrayDropOneLetterVisitor.cpp
 * @author Myles Walker
 */

#include "pch.h"
#include "TrayDropOneLetterVisitor.h"
#include "Tray.h"

void TrayDropOneLetterVisitor::VisitTray(Tray* tray)
{
    // Drop one letter from the tray and store it in mDroppedLetter
    mDroppedLetter = tray->DropSingleLetter();
}