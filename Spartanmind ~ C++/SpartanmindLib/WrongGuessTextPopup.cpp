/**
 * @file WrongGuessTextPopup.cpp
 * @author Simon Oszust
 * @author Jackson White
 */

#include "pch.h"
#include "TextPopup.h"
#include "WrongGuessTextPopup.h"
#include "Game.h"
#include <wx/dcbuffer.h>

/**
 * Custom constructor for the wrong guess popup.
 *
 * @param title The title we want to portray
 * @param line1 The first line to portray
 * @param line2 The second line to portray
 * @param game The game object
 */
WrongGuessTextPopup::WrongGuessTextPopup(const wxString& title, const wxString& line1,
                                         const wxString& line2, Game* game)
    : TextPopup(game), mTitle(title), mLine1(line1), mLine2(line2)
{
    game->SetFrozen(true);
}

/**
 * Overrides draw function for the wrong guess text popup.
 *
 * @param graphics The graphics we are writing on.
 */
void WrongGuessTextPopup::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    // Fixed dimensions for the white box popup.
    double boxWidth = 500;
    double boxHeight = 280;
    double posX = 5 * mGame->TileWidth();
    double posY  = 5 * mGame->TileHeight();

    if (mGame->Level() == 2)
    {
        posX = 9.75 * mGame->TileWidth();
        posY = 7 * mGame->TileHeight();
    }

    // Draw white box with a black border.
    wxBrush rectBrush(*wxWHITE);
    wxPen borderPen(*wxBLACK, 2);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(borderPen);
    graphics->DrawRectangle(posX, posY, boxWidth, boxHeight);

    // Draw the title text in green.
    wxFont titleFont(wxSize(0, 72), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(titleFont, wxColour(10, 171, 29));
    double textWidth, textHeight;
    graphics->GetTextExtent(mTitle, &textWidth, &textHeight);
    double textX = posX + (boxWidth - textWidth) / 2;
    double textY = posY + 10;
    graphics->DrawText(mTitle, textX, textY);

    // Draw additional lines in black.
    wxFont textFont(wxSize(0, 42), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(textFont, *wxBLACK);

    // Line 1
    textY += textHeight + 10;
    graphics->GetTextExtent(mLine1, &textWidth, &textHeight);
    graphics->DrawText(mLine1, posX + (boxWidth - textWidth) / 2, textY);

    // Line 2
    textY += textHeight + 10;
    graphics->GetTextExtent(mLine2, &textWidth, &textHeight);
    graphics->DrawText(mLine2, posX + (boxWidth - textWidth) / 2, textY);
}
