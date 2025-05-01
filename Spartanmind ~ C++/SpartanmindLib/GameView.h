/**
 * @file GameView.h
 * @author Jackson White
 * @author Simon Oszust
 *
 * GameView class which we are going to be using to draw.
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"
#include "TextPopup.h"

/**
 * View class for our Game.
 */
class GameView : public wxWindow {
private:
    /// A list of all the current flying popups we have.
    std::vector<std::shared_ptr<TextPopup>> mPopups;

    /// Stopwatch used to measure elapsed time.
    wxStopWatch mStopWatch;

    /// The last stopwatch time.
    long mTime = 0;

    /// The object that describes our game.
    Game mGame;

    void OnPaint(wxPaintEvent& event);

    void OnLeftDown(wxMouseEvent &event);

    void OnTimer(wxTimerEvent& event);
    void ShowIncorrectPopup(int correct, int wrongSpot);

    void ShowLevelStartPopup(wxString title);
    void ShowLevelStartPopup(wxString title, wxString warning);
    void ShowObstaclePopup();

    void OnKeyDown(wxKeyEvent &event);

    /// Elapsed time in seconds
    int mElapsedSeconds = -3;
    /// Timer to update the scoreboard
    wxTimer mTimer;
    /// Timer for drawing
    wxTimer mTimer2;

    /**
     * Reset the timer.
     */
    void ResetTimer() {mElapsedSeconds = -3; }

public:
    void OnSolve();
    void UpdatePopups();
    void Initialize(wxFrame* parent);
    void OnLoadLevel0();
    void OnLoadLevel1();
    void OnLoadLevel2();
    void OnLoadLevel3();
    void ShowLevelEndPopup();

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //GAMEVIEW_H
