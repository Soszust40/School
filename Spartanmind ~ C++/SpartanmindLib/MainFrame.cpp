/**
 * @file MainFrame.cpp
 * @author Jackson White
 * @author Aditya Menon
 * @author Simon Oszust
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Spartanmind",
        wxDefaultPosition, wxSize(1200,900));

    /// Create a sizer that will lay out child windows vertically
    auto sizer = new wxBoxSizer(wxVERTICAL);

    /// Set the icon to the top right
    wxIcon icon;
    icon.LoadFile(L"images/Spartanmind.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    /// Create the view class object as a child of MainFrame
    mGameView = new GameView();
    mGameView->Initialize(this);

    /// Add it to the sizer
    sizer->Add(mGameView, 1, wxEXPAND | wxALL);

    /// Set the sizer for this frame
    SetSizer(sizer);

    /// Create a menu bar
    auto menuBar = new wxMenuBar();

    /// Create a File menu
    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    /// Append menu items to the File menu
    fileMenu->Append(IDM_SOLVE, "&Solve", "Solve the current level");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    // Append menu items to the Level menu
    levelMenu->Append(IDM_LEVEL0, "Level &0", "Go to Level 0");
    levelMenu->Append(IDM_LEVEL1, "Level &1", "Go to Level 1");
    levelMenu->Append(IDM_LEVEL2, "Level &2", "Go to Level 2");
    levelMenu->Append(IDM_LEVEL3, "Level &3", "Go to Level 3");

    // Append menu items to the Help menu
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    // Append the menus to the menu bar
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(levelMenu, "&Level");
    menuBar->Append(helpMenu, "&Help");

    // Set the menu bar for this frame
    SetMenuBar(menuBar);

    // Remove any existing status bar
    wxStatusBar* oldStatusBar = GetStatusBar();
    if (oldStatusBar)
    {
        SetStatusBar(nullptr);
        delete oldStatusBar;
    }

    // Create a new status bar
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    // Set the size of the window
    SetSize(wxSize(1200, 900));

    // Connect event handlers
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnSolve, this, IDM_SOLVE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevel0, this, IDM_LEVEL0);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevel1, this, IDM_LEVEL1);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevel2, this, IDM_LEVEL2);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevel3, this, IDM_LEVEL3);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

/**
 * Exit menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Spartan Mind Game\n"
                 L"By: MahJong\n"
                 L"\n"
                 L"A variant of the Mastermind game where you guess hidden words.",
                 L"About Spartan Mind",
                 wxOK | wxICON_INFORMATION, this);
}

/**
 * Solve menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnSolve(wxCommandEvent& event)
{
    mGameView->OnSolve();
    mGameView->Refresh();
}

/**
 * Level 0 menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnLevel0(wxCommandEvent& event)
{
    /// lead level0
    mGameView->OnLoadLevel0();
    mGameView->Refresh();
}

/**
 * Level 1 menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnLevel1(wxCommandEvent& event)
{
    mGameView->OnLoadLevel1();
    mGameView->Refresh();
}

/**
 * Level 2 menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnLevel2(wxCommandEvent& event)
{
    mGameView->OnLoadLevel2();
    mGameView->Refresh();
}

/**
 * Level 3 menu option handler.
 * @param event Menu event.
 */
void MainFrame::OnLevel3(wxCommandEvent& event)
{
    mGameView->OnLoadLevel3();
    mGameView->Refresh();
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}