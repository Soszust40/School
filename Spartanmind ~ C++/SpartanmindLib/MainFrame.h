/**
 * @file MainFrame.h
 * @author Jackson White
 * @author Aditya Menon
 * @author Simon Oszust
 * 
 * Main frame for the Sparatmind game.
 */

#ifndef MAHJONG_SPARTANMIND_MAINFRAME_H
#define MAHJONG_SPARTANMIND_MAINFRAME_H

#include "GameView.h"

/**
 * The main frame for the Sparatmind game.
 */
class MainFrame : public wxFrame
{
private:
    /// The game view window
    GameView *mGameView = nullptr;

    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnSolve(wxCommandEvent &event);
    void OnLevel0(wxCommandEvent &event);
    void OnLevel1(wxCommandEvent &event);
    void OnLevel2(wxCommandEvent &event);
    void OnLevel3(wxCommandEvent &event);
    void OnClose(wxCloseEvent& event);

public:
    void Initialize();
};

#endif //MAHJONG_SPARTANMIND_MAINFRAME_H
