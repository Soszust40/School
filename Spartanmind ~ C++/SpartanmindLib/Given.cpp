/**
 * @file Given.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "Given.h"
#include "Item.h"
#include <chrono>

/**
 * Constructor for the given letters.
 * @param game The game this item is a member of.
 * @param imageName The filename of the image for the Given.
 */
Given::Given(Game *game, const std::wstring &imageName) : Item(game, imageName)
{

}

/**
 * Load a letter in.
 * UpCall from Item class, and then store the value of Letter.
 *
 * @param node The item node.
 * @param declaration The declaration node.
 */
void Given::XmlLoad(wxXmlNode *node, wxXmlNode *declaration)
{
    Item::XmlLoad(node, declaration);
    declaration->GetAttribute(L"value").ToInt(&mValue);
}