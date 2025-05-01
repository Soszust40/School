project(SpartanmindLib)

# Sources files here
set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        Letter.cpp
        Letter.h
        Player.cpp
        Player.h
        Tray.cpp
        Tray.h
        Background.cpp
        Background.h
        TextPopup.cpp
        TextPopup.h
        TextPopupObstacle.cpp
        TextPopupObstacle.h
        Loader.cpp
        Loader.h
        Given.cpp
        Given.h
        ItemVisitor.cpp
        ItemVisitor.h
        LetterPickerUpperVisitor.cpp
        LetterPickerUpperVisitor.h
        TrayAddLetterVisitor.cpp
        TrayAddLetterVisitor.h
        TraysLettersVisitor.cpp
        TraysLettersVisitor.h
        TrayRemoveLetterVisitor.cpp
        TrayRemoveLetterVisitor.h
        InvisibleAnswer.cpp
        InvisibleAnswer.h
        Container.cpp
        Container.h
        LetterVisitorValue.cpp
        LetterVisitorValue.h
        GivenValueVisitior.cpp
        GivenValueVisitior.h
        ContainerAddLetterVisitor.cpp
        ContainerAddLetterVisitor.h
        LetterSolverVisitor.cpp
        LetterSolverVisitor.h
        Obstacle.cpp
        Obstacle.h
        ContainerOpenVisitor.cpp
        ContainerOpenVisitor.h
        ContainerHeadButtVisitor.cpp
        ContainerHeadButtVisitor.h
        ObstacleVisitorHitTest.cpp
        ObstacleVisitorHitTest.h
        StartTextPopup.cpp
        StartTextPopup.h
        EndTextPopup.cpp
        EndTextPopup.h
        ChestFullTextPopup.cpp
        ChestFullTextPopup.h
        WrongGuessTextPopup.cpp
        WrongGuessTextPopup.h
        PopupVisitor.cpp
        PopupVisitor.h
        EndPopupVisitor.cpp
        EndPopupVisitor.h
        StartPopupVisitor.cpp
        StartPopupVisitor.h
        Picture.cpp
        Picture.h
        TrayDropOneLetterVisitor.cpp
        TrayDropOneLetterVisitor.h
        LetterTrayCoordinateSetterVisitor.cpp
        LetterTrayCoordinateSetterVisitor.h
        LetterInTrayDrawer.cpp
        LetterInTrayDrawer.h
        LetterCoordVisitor.cpp
        LetterCoordVisitor.h
)

# Turn off wxWidgets own precompiled header system and
set(wxBUILD_PRECOMP OFF)
# Request the required wxWidget libs
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

# Creating the library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Linking library
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# This MIGHT need to be in here im not sure
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)