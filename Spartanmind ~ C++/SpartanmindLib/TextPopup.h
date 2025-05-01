/**
 * @file TextPopup.h
 * @author Simon Oszust
 *
 * Class that creates text popups.
 */

#ifndef TEXTPOPUP_H
#define TEXTPOPUP_H

#include "PopupVisitor.h"
#include "Game.h"
#include <wx/timer.h>
#include <wx/graphics.h>

class Game;

/**
* Class that describes a TextPopup.
*/
class TextPopup {
public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we are accepting.
     */
    virtual void Accept(PopupVisitor * visitor) = 0;

    TextPopup(Game* game);

    /**
     * Default destructor
     */
    virtual ~TextPopup() = default;

    /**
     * Pure virtual draw function that is going to be overriden by each popup class.
     * @param graphics the graphics to write to.
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Return if the text popup is expired.
     *
     * @return Bool if the popup is expired.
     */
    bool IsExpired() { return mExpired; }

    /**
     * Virtual function that is overriden for some classes that unfreeze the game.
     *
     * @return Bool if the popup can unfreeze the game.
     */
    virtual bool UnFreeze() { return false; }

protected:
    /// The game object for our popup
    Game* mGame = nullptr;
    /// Boolean if the text popup is expired
    bool mExpired;
    /// The timer we start
    wxTimer mTimer;

    void OnTimer(wxTimerEvent& event);
};

#endif //TEXTPOPUP_H