/**
 * @file Picture.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "Picture.h"

using namespace std;

/**
 * Constructor for Picture item.
 * @param imageName The image name of picture.
 */
Picture::Picture(std::wstring imageName)
{
    mImage = make_shared<wxImage>(imageName);
    mBitmap = make_shared<wxBitmap>(*mImage);
}