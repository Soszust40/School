/**
 * @file Spartanmind.cpp
 * @author Noah Patenaude
 *
 * The Spartanmind cpp file
 */

#include "pch.h"
#include "Spartanmind.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return bool : if the app was initialized or not
 */
bool Spartanmind::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
