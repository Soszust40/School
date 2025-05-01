/**
 * @file WrongGuessTextPopup.h
 * @author Simon Oszust
 *
 * Class that creates text popup for wrong guess.
 */

#ifndef WRONGGUESSTEXTPOPUP_H
#define WRONGGUESSTEXTPOPUP_H

class TextPopup;

/**
 * Wrong guess text popup that is derived from TextPopup Class.
 *
 * This popup freezes the game and portrays the amount of correct/incorrect letters.
 */
class WrongGuessTextPopup : public TextPopup {
public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(PopupVisitor* visitor) override { visitor->VisitWrongPopup(this); }
    WrongGuessTextPopup(const wxString& title, const wxString& line1, const wxString& line2, Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

private:
    /// The words we want to portray to the screen
    wxString mTitle;
    /// The first line we want to portray
    wxString mLine1;
    /// The second line we want to portray
    wxString mLine2;
};

#endif //WRONGGUESSTEXTPOPUP_H
