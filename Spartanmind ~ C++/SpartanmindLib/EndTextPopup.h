/**
 * @file EndTextPopup.h
 * @author Simon Oszust
 * @author Jackson White
 *
 * Class that creates text popup for end of level.
 */

#ifndef ENDTEXTPOPUP_H
#define ENDTEXTPOPUP_H

class TextPopup;

/**
 * End text popup derived from Text Popup.
 *
 * This is the end text popup that shows up.
 */
class EndTextPopup : public TextPopup {
public:

    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(PopupVisitor* visitor) override { visitor->VisitEndPopup(this); }

    EndTextPopup(const wxString& title, Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

private:
    /// The title want to portray on the popup.
    wxString mTitle;
};

#endif //ENDTEXTPOPUP_H
