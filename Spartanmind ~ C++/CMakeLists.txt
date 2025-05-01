# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.24)
project(mahjong_spartanmind)
set(CMAKE_CXX_STANDARD 20)

# Linking to the lib
set(APPLICATION_LIBRARY SpartanmindLib)

# Turn off wxWidgets own precompiled header system and
set(wxBUILD_PRECOMP OFF)
# Request the required wxWidget libs
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

# Add include directories
include_directories(${wxWidgets_INCLUDE_DIRS})

# Copying the lib over
add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Sources files here
set(SOURCE_FILES main.cpp
        Spartanmind.cpp
        Spartanmind.h
        pch.h)


# copy the imges folder and level folder to cmake build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Linking the libraries
target_link_libraries(${PROJECT_NAME} SpartanmindLib)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

add_subdirectory(Tests)

