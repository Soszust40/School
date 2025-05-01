/**
 * @file Background.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "Background.h"

/**
 * Constructor for the background object.
 * @param game The game this item is a member of.
 * @param imageName The filename of the image for the Background.
 */
Background::Background(Game *game, const std::wstring &imageName) : Item(game, imageName)
{

}