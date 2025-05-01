/**
 * @file TrayTest.cpp
 * @author Jackson White
 */

#include <pch.h>
#include <Letter.h>
#include <Game.h>
#include <Tray.h>
#include <gtest/gtest.h>

/// Letter filename
const std::wstring LetterImageName = L"images/cl.png";

/**
 * Create a tray node.
 *
 * @return wxXmlNode for the Tray object.
 */
wxXmlNode* CreateTrayNode()
{
    // Create the tray element node
    wxXmlNode* trayNode = new wxXmlNode(wxXML_ELEMENT_NODE, "tray");

    // Add the attributes
    trayNode->AddAttribute("id", "i584");
    trayNode->AddAttribute("col", "16.5");
    trayNode->AddAttribute("row", "2.5");

    // Note: This element has no text content, just attributes

    return trayNode;
}

/**
 * Create a declaration node for Tray.
 *
 * @return declaration node for the tray.
 */
wxXmlNode* CreateDeclarationNode()
{
    // Create the tray element node
    wxXmlNode* trayNode = new wxXmlNode(wxXML_ELEMENT_NODE, "tray");

    // Add all the attributes
    trayNode->AddAttribute("id", "i584");
    trayNode->AddAttribute("width", "144");
    trayNode->AddAttribute("height", "144");
    trayNode->AddAttribute("image", "tray.png");
    trayNode->AddAttribute("capacity", "4");

    return trayNode;
}

/// Test for adding letters to the Tray.
TEST(TrayTest, AddLetterAndContainersLetter)
{
    wxXmlNode* trayNode = CreateTrayNode();
    wxXmlNode* declarationNode = CreateDeclarationNode();
    Game game;
    Tray tray(&game, L"");
    tray.XmlLoad(trayNode, declarationNode);

    auto letter = std::make_shared<Letter>(&game, LetterImageName);

    ASSERT_FALSE(tray.ContainsLetter(letter));

    tray.AddLetter(letter);

    ASSERT_TRUE(tray.ContainsLetter(letter));
}

/// Test for loading the Tray from XML.
TEST(TrayTest, XmlLoad)
{
    wxXmlNode* trayNode = CreateTrayNode();
    wxXmlNode* declarationNode = CreateDeclarationNode();
    Game game;
    Tray tray(&game, L"");
    tray.XmlLoad(trayNode, declarationNode);

    ASSERT_EQ(tray.GetWidth(), 144) <<
        L"width of tray should be 144";
    ASSERT_EQ(tray.GetHeight(), 144) <<
        L"height of tray should be 144";
    ASSERT_EQ(tray.GetCapacity(), 4) <<
        L"capacity of tray should be 4";
    ASSERT_EQ(tray.GetX(), 16.5) <<
        L"x of tray should be 16.5";
    ASSERT_EQ(tray.GetY(), 2.5) <<
        L"y of tray should be 2.5";
}

/// Check if the isFull method is working.
TEST(TrayTest, IsFull)
{
    wxXmlNode* trayNode = CreateTrayNode();
    wxXmlNode* declarationNode = CreateDeclarationNode();
    Game game;
    Tray tray(&game, L"");
    tray.XmlLoad(trayNode, declarationNode);

    auto letter = std::make_shared<Letter>(&game, LetterImageName);

    tray.AddLetter(letter);
    ASSERT_FALSE(tray.IsFull()) <<
        L"Tray hasnt reached capactiy yet";
    tray.AddLetter(letter);
    ASSERT_FALSE(tray.IsFull())<<
        L"Tray hasnt reached capactiy yet";
    tray.AddLetter(letter);
    ASSERT_FALSE(tray.IsFull())<<
        L"Tray hasnt reached capactiy yet";
    tray.AddLetter(letter);
    ASSERT_TRUE(tray.IsFull())<<
        L"Tray capacity is 4 and we have added 4 letters. should finally be true";
}