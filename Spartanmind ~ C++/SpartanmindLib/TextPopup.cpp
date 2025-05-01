/**
 * @file TextPopup.cpp
 * @author Simon Oszust
 * @author Jackson White
 */

#include "pch.h"
#include "TextPopup.h"
#include "Game.h"
#include <wx/dcbuffer.h>

/**
 * Constructor the text popup class.
 * @param game The game object.
 */
TextPopup::TextPopup(Game* game) : mGame(game), mExpired(false) {
    mTimer.Bind(wxEVT_TIMER, &TextPopup::OnTimer, this);
    mTimer.Start(3000, wxTIMER_ONE_SHOT);
}

/**
 * When the timer goes off, set the popup as expired.
 * @param event Timer event to handle.
 */
void TextPopup::OnTimer(wxTimerEvent& event) {
    mExpired = true;
}