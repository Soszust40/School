/**
 * @file StartPopupVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "StartPopupVisitor.h"

/**
 * Overrides vistitstartpopup function that adds to the count of start popups.
 * @param popup The popup we are visiting.
 */
void StartPopupVisitor::VisitStartPopup(StartTextPopup* popup)
{
    mNumStart += 1;
}
