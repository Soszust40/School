/**
 * @file StartTextPopup.cpp
 * @author Simon Oszust
 * @author Jackson White
 */

#include "pch.h"
#include "TextPopup.h"
#include "StartTextPopup.h"
#include "Game.h"
#include <wx/dcbuffer.h>

/**
 * Custom constructor for the start text popup.
 *
 * @param title The title we want to show.
 * @param line1 The first line we want to show.
 * @param line2 The second line of the popup.
 * @param line3 The third line of the popup.
 * @param game The game object.
 */
StartTextPopup::StartTextPopup(const wxString& title, const wxString& line1,
                               const wxString& line2, const wxString& line3, Game* game)
    : TextPopup(game), mTitle(title), mLine1(line1), mLine2(line2), mLine3(line3), mLine4("")
{
    game->SetFrozen(true);
}

/**
 * Custom constructor for the start text popup.
 *
 * @param title The title we want to show.
 * @param line1 The first line we want to show.
 * @param line2 The second line of the popup.
 * @param line3 The third line of the popup.
 * @param line4 the fourth line of the popup
 * @param game The game object.
 */
StartTextPopup::StartTextPopup(const wxString& title, const wxString& line1,
                               const wxString& line2, const wxString& line3, const wxString& line4, Game* game)
    : TextPopup(game), mTitle(title), mLine1(line1), mLine2(line2), mLine3(line3), mLine4(line4)
{
    game->SetFrozen(true);
}

/**
 * Custom overrides draw function for the start text popup.
 * @param graphics The graphics we are writing to.
 */
void StartTextPopup::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
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

    if (mLine4 != "")
    {
        boxWidth += 20;
        boxHeight += 50;
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

    // Line 3
    textY += textHeight + 10;
    graphics->GetTextExtent(mLine3, &textWidth, &textHeight);
    graphics->DrawText(mLine3, posX + (boxWidth - textWidth) / 2, textY);

    if (mLine4 != "")
    {
        textY += textHeight + 10;
        graphics->GetTextExtent(mLine4, &textWidth, &textHeight);
        graphics->DrawText(mLine4, posX + (boxWidth - textWidth) / 2, textY);
    }
}