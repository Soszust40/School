/**
* @file ChestFullTextPopup.cpp
* @author Simon Oszust
* @author Jackson White
*/

#include "pch.h"
#include "TextPopup.h"
#include "ChestFullTextPopup.h"
#include "Game.h"
#include <wx/dcbuffer.h>

/**
 * Custom Constructor the ChestFullTextPopup.
 *
 * @param title The main line of the popup.
 * @param game The game object.
 */
ChestFullTextPopup::ChestFullTextPopup(const wxString& title, Game* game)
    : TextPopup(game), mFlyingText(title) {
    mFlyingTextY = mGame->GetHeight() * mGame->TileHeight();
    mFlyingTextSpeed = 300;
    mFlyingTimer.Bind(wxEVT_TIMER, &ChestFullTextPopup::OnFlyingTimer, this);
    mFlyingTimer.Start(5);
    mTime = mStopWatch.Time();
}

/**
 * A timer handler for the timer event.
 * This function adjusts the position of the flying text popup.
 *
 * @param event The event we are handling.
 */
void ChestFullTextPopup::OnFlyingTimer(wxTimerEvent& event) {
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mFlyingTextY -= mFlyingTextSpeed * elapsed;

    if (mFlyingTextY < -50) {
        mFlyingTimer.Stop();
        mExpired = true;
    }
}

/**
 * Overrides draw function to draw our flying text popup.
 *
 * @param graphics Graphics we are drawing to.
 */
void ChestFullTextPopup::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    // Draw flying red text.
    wxFont textFont(wxSize(0, 32), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(textFont, *wxRED);
    double textWidth, textHeight;

    graphics->GetTextExtent(mFlyingText, &textWidth, &textHeight);

    double textX =  6.3 * mGame->TileWidth();

    if (mGame->Level() == 2)
    {
        textX =  11.3 * mGame->TileWidth();
    }

    wxBrush rectBrush(*wxWHITE);
    wxPen borderPen(*wxBLACK, 4);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(borderPen);
    if (mFlyingText == "Something is already there!")
    {
        graphics->DrawRectangle(textX-40, mFlyingTextY, textWidth+20, textHeight);
        graphics->DrawText(mFlyingText, textX-30, mFlyingTextY);
    }
    else
    {
        graphics->DrawRectangle(textX-10, mFlyingTextY, textWidth+20, textHeight);
        graphics->DrawText(mFlyingText, textX, mFlyingTextY);
    }
}