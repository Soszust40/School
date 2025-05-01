/**
 * @file TextPopupObstacle.h
 * @author Aditya Menon
 *
 * Class that creates text popup for obstacle collision.
 */

#ifndef TEXTPOPUPOBSTACLE_H
#define TEXTPOPUPOBSTACLE_H

class TextPopup;

/**
 * Obstacle popup derived class from text popup. It is used for obstacle collision popup.
 */
class TextPopupObstacle : public TextPopup {
public:

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(PopupVisitor* visitor) override { visitor->VisitObstaclePopup(this); }

    TextPopupObstacle(const wxString& title, Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Override the unfreeze function.
     * @return Always returns true.
     */
    bool UnFreeze() override { return true; }

private:
    /// Flying text we want to portray.
    wxString mFlyingText;
    /// The timer for the popup.
    wxTimer mFlyingTimer;
    /// The position in the y coordinates that the popup appears.
    double mFlyingTextY;
    /// The flying speed that we want.
    double mFlyingTextSpeed;
    /// The stopwatch for the flying text.
    wxStopWatch mStopWatch;
    /// The amount of time elapsed.
    long mTime;

    void OnFlyingTimer(wxTimerEvent& event);
};

#endif //TEXTPOPUPOBSTACLE_H 