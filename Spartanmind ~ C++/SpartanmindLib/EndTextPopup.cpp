/**
 * @file EndTextPopup.cpp
 * @author Simon Oszust
 * @author Jackson White
 */

#include "pch.h"
#include "TextPopup.h"
#include "EndTextPopup.h"
#include "Game.h"
#include <wx/dcbuffer.h>

/**
 * Custom constructor for the end text popup.
 *
 * @param title The title we want to portray.
 * @param game The game object.
 */
EndTextPopup::EndTextPopup(const wxString& title, Game* game)
    : TextPopup(game), mTitle(title)
{
    game->SetFrozen(true);
}

/**
 *  Overrides draw function to draw the end text popup.
 *
 * @param graphics The graphics we are writing to.
 */
void EndTextPopup::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    // Draw centered green title text.
    wxFont titleFont(wxSize(0, 94), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(titleFont, wxColour(10, 171, 29));
    double textWidth, textHeight;
    graphics->GetTextExtent(mTitle, &textWidth, &textHeight);

    double textX =  2.5 * mGame->TileWidth();
    double textY =  7 * mGame->TileWidth();

    if (mGame->Level() == 2)
    {
        textX =  7.5 * mGame->TileWidth();
        textY =  8.5 * mGame->TileWidth();
    }
    graphics->DrawText(mTitle, textX, textY);
}
