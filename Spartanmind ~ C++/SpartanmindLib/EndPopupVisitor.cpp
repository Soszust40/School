/**
 * @file EndPopupVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "EndPopupVisitor.h"

/**
 * Overrides VisitEndPopup function that adds to the count of total end popups.
 * @param popup The popup we are visiting.
 */
void EndPopupVisitor::VisitEndPopup(EndTextPopup* popup)
{
    mEndPopup += 1;
}