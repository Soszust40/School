/**
 * @file StartTextPopup.h
 * @author Simon Oszust
 *
 * Class that creates text popup for start of level.
 */

#ifndef STARTTEXTPOPUP_H
#define STARTTEXTPOPUP_H

class TextPopup;

/**
 * Start text popup derived from TextPopup Class.
 *
 * Is the popup you see when you first load the game.
 */
class StartTextPopup : public TextPopup {
public:

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(PopupVisitor* visitor) override { visitor->VisitStartPopup(this); }
    StartTextPopup(const wxString& title, const wxString& line1,
                           const wxString& line2, const wxString& line3, Game* game);
    StartTextPopup(const wxString& title, const wxString& line1, const wxString& line2, const wxString& line3,
                   const wxString& line4, Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

private:
    /// The words we want to portray to the screen
    wxString mTitle;
    /// The first line we want to portray
    wxString mLine1;
    /// The second line we want to portray
    wxString mLine2;
    /// The third line we want to portray
    wxString mLine3;
    /// The fourth line we want to portray
    wxString mLine4;
};

#endif //STARTTEXTPOPUP_H
