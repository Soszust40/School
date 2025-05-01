/**
 * @file GameTest.cpp
 * @author Jackson White
 *
 * Tests for our Game class.
 */

#include <pch.h>
#include <Game.h>
#include <Given.h>
#include <Player.h>
#include <Letter.h>
#include <regex>
#include <fstream>
#include <gtest/gtest.h>

/// Zero level xml
const std::wstring Level0 = L"levels/level0.xml";
/// First level xml
const std::wstring Level1 = L"levels/level1.xml";
/// Second level xml
const std::wstring Level2 = L"levels/level2.xml";

using namespace std;

/// Test that the game is constructing.
TEST(GameTest, Construct)
{
    Game game;
}

/// Test that the game is loading correctly.
TEST(GameTest, Load)
{
    Game game;
    /// level 0 test
    game.OnLoadLevel(Level0);

    ASSERT_EQ(game.Level(), 0) <<
        L"Level 0 check";

    ASSERT_EQ(game.TileWidth(), 48) <<
        L"Tile width of level 1 is 48";

    ASSERT_EQ(game.TileHeight(), 48) <<
        L"Tile width of level 1 is 48";

    ASSERT_TRUE(game.GetPlayer()->GetId() == "i382") <<
        L"ID of player level 0 is i382";

    ASSERT_TRUE(game.GetHeight() == 15) <<
        L"Height of level 0 is 15";

    ASSERT_TRUE(game.GetWidth() == 20) <<
        L"Width of level 0 is 20";

    /// level 1 test
    game.OnLoadLevel(Level1);

    ASSERT_EQ(game.Level(), 1) <<
        L"Level 1 check";

    ASSERT_EQ(game.TileWidth(), 48) <<
        L"Tile width of level 1 is 48";

    ASSERT_EQ(game.TileHeight(), 48) <<
        L"Tile width of level 1 is 48";

    ASSERT_TRUE(game.GetPlayer()->GetId() == "i582") <<
    L"ID of player level 1 is i582";

    ASSERT_TRUE(game.GetHeight() == 15) <<
    L"Height of level 1 is 15";

    ASSERT_TRUE(game.GetWidth() == 20) <<
        L"Width of level 1 is 20";

    /// level 2 test
    game.OnLoadLevel(Level2);

    ASSERT_EQ(game.Level(), 2) <<
        L"Level 1 check";

    ASSERT_EQ(game.TileWidth(), 48) <<
        L"Tile width of level 1 is 48";

    ASSERT_EQ(game.TileHeight(), 48) <<
        L"Tile width of level 1 is 48";

    ASSERT_TRUE(game.GetPlayer()->GetId() == "i250") <<
        L"ID of player level 1 is i250";

    ASSERT_TRUE(game.GetHeight() == 20) <<
    L"Height of level 2 is 30";

    ASSERT_TRUE(game.GetWidth() == 30) <<
        L"Width of level 2 is 30";
}

/// Test the hitTest function.
TEST(GameTest, HitTest)
{
    Game game;

    game.Clear();

    ASSERT_EQ(game.HitTest(100, 200), nullptr) <<
        L"Testing empty game";

    shared_ptr<Letter> letter1 = make_shared<Letter>(&game,L"images/al.png");
    game.AddItem(letter1);
    letter1->SetLocation(5, 10);

    auto xcoord = 243 * game.GetScale() + game.GetOffsetX();
    auto ycoord =483 * game.GetScale()+ game.GetOffsetY();
    ASSERT_TRUE(game.HitTest(xcoord, ycoord) == letter1) <<
        L"Testing Letter at 243, 483";

    shared_ptr<Given> given1 = make_shared<Given>(&game,L"images/ad.png");
    game.AddItem(given1);
    given1->SetLocation(7, 4);

    xcoord = 339 * game.GetScale() + game.GetOffsetX();
    ycoord = 195 * game.GetScale()+ game.GetOffsetY();
    ASSERT_TRUE(game.HitTest(xcoord, ycoord) == given1) <<
    L"Testing Given at 339, 195";

    shared_ptr<Letter> letter4 = make_shared<Letter>(&game,L"images/al.png");
    game.AddItem(letter4);
    letter4->SetLocation(5, 10);

    xcoord = 243 * game.GetScale() + game.GetOffsetX();
    ycoord =483 * game.GetScale()+ game.GetOffsetY();
    ASSERT_TRUE(game.HitTest(xcoord, ycoord) == letter4) <<
        L"Testing Letter at 243, 483";

    shared_ptr<Letter> letter5 = make_shared<Letter>(&game,L"images/pl.png");
    game.AddItem(letter5);
    letter5->SetLocation(14, 10);

    xcoord = (695.4613) * game.GetScale()+ game.GetOffsetX();
    ycoord =(498.25436) * game.GetScale() + game.GetOffsetY();;
    ASSERT_TRUE(game.HitTest(xcoord, ycoord) == letter5) <<
        L"Testing Letter at 695, 498";
}