/**
 * @file InvisibleAnswerTest.cpp
 * @author Jackson White
 */

#include <pch.h>
#include <Letter.h>
#include <Game.h>
#include <InvisibleAnswer.h>
#include <gtest/gtest.h>

/// Letter filename
const std::wstring LetterImageName = L"images/cl.png";

/**
 * Create a xml Node * for the game.
 * @return A XMLNode* to the game.
 */
wxXmlNode* CreateGameNode()
{
    // Create the game element node
    wxXmlNode* gameNode = new wxXmlNode(wxXML_ELEMENT_NODE, "game");

    // Add the attributes
    gameNode->AddAttribute("col", "7");
    gameNode->AddAttribute("row", "4");
    gameNode->AddAttribute("length", "6");

    // Add the text content (the numbers)
    gameNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, "", "19 20 17 8 13 6"));

    return gameNode;
}

/// Test to check if the spot was filled.
TEST(InvisibleAnswerTest, SpotFilled)
{
    Game game;
    InvisibleAnswer invisibleAnswer;
    wxXmlNode* gameNode = CreateGameNode();
    invisibleAnswer.XmlLoad(gameNode);

    auto letter = std::make_shared<Letter>(&game, LetterImageName);

    ASSERT_FALSE(invisibleAnswer.SpotFilled(letter, 7)) << L"Spot shouldnt be filled yet";

    ASSERT_TRUE(invisibleAnswer.SpotFilled(letter, 7)) << L"Spot is now filled";

}

/// HitTest the InvisibleAnswer.
TEST(InvisibleAnswerTest, HitTest)
{
    Game game;
    InvisibleAnswer invisibleAnswer;
    wxXmlNode* gameNode = CreateGameNode();
    invisibleAnswer.XmlLoad(gameNode);

    ASSERT_TRUE(invisibleAnswer.HitTest(7,4)) <<
        L"Hit where the spot is";

    ASSERT_FALSE(invisibleAnswer.HitTest(6,4)) <<
        L"Hit to the left of the invisible answer";

    ASSERT_TRUE(invisibleAnswer.HitTest(13,4)) <<
        L"Hit to the last spot of the invisible answer";

    ASSERT_FALSE(invisibleAnswer.HitTest(6,5)) <<
        L"Hit to the above of the invisible answer";
}