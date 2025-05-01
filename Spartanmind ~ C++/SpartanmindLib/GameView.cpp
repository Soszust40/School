/**
 * @file GameView.cpp
 * @author Jackson White
 * @author Simon Oszust
 */

#include "pch.h"
#include "GameView.h"
#include "TextPopup.h"
#include "ChestFullTextPopup.h"
#include "EndPopupVisitor.h"
#include "EndTextPopup.h"
#include "StartPopupVisitor.h"
#include "StartTextPopup.h"
#include "WrongGuessTextPopup.h"
#include "TextPopupObstacle.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

/// First level xml level0
const std::wstring Level0 = L"levels/level0.xml";
/// First level xml level1
const std::wstring Level1 = L"levels/level1.xml";
/// First level xml level2
const std::wstring Level2 = L"levels/level2.xml";
/// First level xml level3
const std::wstring Level3 = L"levels/level3.xml";

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

using namespace std;
/**
 * The top-left position of the scoreboard in virtual pixels.
 * @return WxPoint representing the (x, y) position.
 */
const wxPoint ScoreboardTopLeft(10, 10);

/**
 * Initialize the game view class.
 * @param parent The parent window for this class.
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
       wxDefaultPosition, wxDefaultSize,
       wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);

    /// Level 1 Begin Text
    ShowLevelStartPopup("Level 1 Begin");
    mStopWatch.Start();

    /// Had to use setowner to make sure it binds to the gameview without making a constructor
    mTimer.SetOwner(this, wxID_ANY);
    if (!mTimer.IsRunning())
    {
        mTimer.Start(1000); // Tick every 1 second
    }

    mTimer2.SetOwner(this, wxID_ANY);
    if (!mTimer2.IsRunning())
    {
        mTimer2.Start(50); // Tick every 1 second
    }
}

/**
 * Paint event, draws the window.
 * @param event Paint event object.
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    /// Compute the time that has elapsed
    /// since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    /// Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    /// Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    /// Draw Scoreboard Timer
    int minutes = mElapsedSeconds / 60;
    int seconds = mElapsedSeconds % 60;

    wxFont font(wxSize(0, ScoreboardTextSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gc->SetFont(font, *wxWHITE);

    mGame.SetScaleAndTranslation(gc);
    if (minutes <= 0 && seconds < 0)
    {
        wxString timeText = wxString::Format("%d:%02d", 0 ,0);
        gc->DrawText(timeText, 10, 10);
    }
    else
    {
        wxString timeText = wxString::Format("%d:%02d", minutes, seconds);
        gc->DrawText(timeText, 10, 10);
    }

    for (auto& popup : mPopups)
    {
        popup->Draw(gc);
    }

    UpdatePopups();
    gc->PopState();
}

/**
 * Handle the left mouse button down event.
 * @param event The mouse event.
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());
    Refresh();
}

/**
 * Handles timer events to update the scoreboard time.
 * @param event The timer event.
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    // Check if obstacle was hit
    if (mGame.WasObstacleHit())
    {
        mGame.SetObstacleHit(false); // Reset the flag
        ShowObstaclePopup();
    }

    if (mGame.IsFilledOut())
    {
        if (mGame.GameIsComplete())
        {
            ShowLevelEndPopup();
            UpdatePopups();
            if (mGame.IsFrozen())
            {
                return;
            }

            if (mGame.Level() == 0)
            {
                OnLoadLevel1();
            }
            else if (mGame.Level() == 1)
            {
                OnLoadLevel2();
            }
            else if (mGame.Level() == 2)
            {
                OnLoadLevel3();
            }
            else if (mGame.Level() == 3)
            {
                OnLoadLevel3();
            }
        }
        else
        {
            int correct = mGame.GetCorrectLetters();
            int wrongSpot = mGame.WrongSpot();

            ShowIncorrectPopup(correct, wrongSpot);
            UpdatePopups();

            if (mGame.IsFrozen())
            {
                return;
            }
            mPopups.clear();
            if (mGame.Level() == 0)
            {
                mGame.OnLoadLevel(Level0);
                Refresh();
            }
            else if (mGame.Level() == 1)
            {
                mGame.OnLoadLevel(Level1);
                Refresh();
            }
            else if (mGame.Level() == 2)
            {
                mGame.OnLoadLevel(Level2);
                Refresh();
            }
            else if (mGame.Level() == 3)
            {
                mGame.OnLoadLevel(Level3);
                Refresh();
            }
        }
    }

    else if (event.GetId() == mTimer.GetId())
    {
        mElapsedSeconds++; // Increment seconds
        Refresh(); // Redraw screen to update timer display
    }
    else
    {
        Refresh(); // Redraw screen to update timer display
    }
}

/**
 * Popup for the wrong solution.
 *
 * @param correct The number of letters in the correct spot.
 * @param wrongSpot The number of letters in the wrong spot.
 */
void GameView::ShowIncorrectPopup(int correct, int wrongSpot)
{
    auto popup = make_shared<WrongGuessTextPopup>("Incorrect!", "Matched Letters: " + to_string(correct),
        "Existing Letters: " + to_string(wrongSpot) ,&mGame);
    mPopups.push_back(popup);
    Refresh(); // Trigger a repaint so the new popup appears.
}

/**
 * Show the Level begin popup.
 *
 * @param title What the title of the message should display.
 */
void GameView::ShowLevelStartPopup(wxString title)
{
    mPopups.clear();
    auto popup = make_shared<StartTextPopup>(title, "Spacebar: Grab", "A-Z,-: Release", "Shift: Headbutt", &mGame);
    mPopups.push_back(popup);
    Refresh(); // Trigger a repaint so the new popup appears.
}

/**
 * Show the Level begin popup with a warning text
 *
 * @param title What the title of the message should display.
 * @param warning the warning we are going to show
 */
void GameView::ShowLevelStartPopup(wxString title, wxString warning)
{
    mPopups.clear();
    auto popup = make_shared<StartTextPopup>(title, "Spacebar: Grab", "A-Z,-: Release", "Shift: Headbutt", warning, &mGame);
    mPopups.push_back(popup);
}

/**
 * Show the Level End popup.
 */
void GameView::ShowLevelEndPopup()
{
    EndPopupVisitor popupVisitor;
    StartPopupVisitor startVisitor;
    for (auto popup : mPopups)
    {
        popup->Accept(&popupVisitor);
        popup->Accept(&startVisitor);
    }
    if (startVisitor.NumStart() > 0)
    {
        mPopups.erase(mPopups.begin());
    }
    if (popupVisitor.NumEndPopup() == 0)
    {
        auto popup = make_shared<EndTextPopup>("Level Complete!", &mGame);
        mPopups.push_back(popup);
    }
    Refresh(); // Trigger a repaint so the new popup appears.
}

/**
 * Load Level 0.
 * Will be used in the binded function LoadLevel0.
 */
void GameView::OnLoadLevel0()
{
    mGame.OnLoadLevel(Level0);
    Refresh();
    ShowLevelStartPopup("Level 0 Begin");
    ResetTimer();
}

/**
 * Load Level 1.
 * Will be used in the binded function LoadLevel1.
 */
void GameView::OnLoadLevel1()
{
    mGame.OnLoadLevel(Level1);
    Refresh();
    ShowLevelStartPopup("Level 1 Begin");
    ResetTimer();
}

/**
 * Load Level 2.
 * Will be used in the binded function LoadLevel2.
 */
void GameView::OnLoadLevel2()
{
    mGame.OnLoadLevel(Level2);
    Refresh();
    ShowLevelStartPopup("Level 2 Begin");
    ResetTimer();
}

/**
 * Load Level 3.
 * Will be used in the binded function LoadLevel3.
 */
void GameView::OnLoadLevel3()
{
    mGame.OnLoadLevel(Level3);
    Refresh();
    ShowLevelStartPopup("Level 3 Begin", "Don't Hit The Obstacles!");
    ResetTimer();
}

/**
 * Handle the event of a key being pushed down.
 * @param event The key event.
 */
void GameView::OnKeyDown(wxKeyEvent &event)
{
    int key = event.GetKeyCode(); 
    
    if (key == WXK_SPACE)
    {
        /// Signal to the game or player that the spacebar has been pressed.
        bool chestFull = mGame.StartSpaceAnimation();

        if (chestFull)
        {
            auto popup = make_shared<ChestFullTextPopup>("Max Capacity Reached!", &mGame);
            mPopups.push_back(popup);
        }
    }
    else if (key == WXK_SHIFT)
    {
        /// Signal to the game that the shift button has been pressed
        mGame.StartShiftAnimation(event.GetX(), event.GetY());
    }

    else if ((key >= 'A' && key <= 'Z') || key == '-')
    {
        /// Send the key press to the Game class, which handles all the logic
        /// for finding the matching letter in the tray and placing it
        bool letterPlaced = mGame.PlaceLetter(key);
        
        if (letterPlaced)
        {
            Refresh(); /// Refresh the view to show the placed letter
        }
        else
        {
            auto popup = make_shared<ChestFullTextPopup>("Something is already there!", &mGame);
            mPopups.push_back(popup);
        }
    }
    event.Skip();
}

/**
 * Solve the game when OnSolve event is called.
 */
void GameView::OnSolve()
{
    mGame.SolveGame();
}

/**
 * Iterate through all the popups and check if they expired.
 */
void GameView::UpdatePopups()
{
    for (auto item = mPopups.begin(); item != mPopups.end();)
    {
        if ((*item)->IsExpired())
        {
            if (!(*item)->UnFreeze())
            {
                mGame.SetFrozen(false);
            }
            item = mPopups.erase(item);
        }
        else
        {
            ++item;
        }
    }
}

/**
 * Show the obstacle collision popup.
 */
void GameView::ShowObstaclePopup()
{
    auto popup = make_shared<TextPopupObstacle>("You Crashed!", &mGame);
    mPopups.push_back(popup);
}