/**
 * @file ItemTest.cpp
 * @author Jackson White
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>

/// letter filename
const std::wstring LetterImageName = L"images/cl.png";

/**
 * Mock class for testing the class Item.
 */
class ItemMock : public Item {
public:
    void Accept(ItemVisitor* visitor) override { }
    ItemMock(Game *game) : Item(game, LetterImageName) {}
};

/// Test for making sure letter items are placed where they should be.
TEST(ItemTest, HitTest)
{
    Game game;
    ItemMock item(&game);

    item.SetLocation(5, 10);

    auto xcoord =  243;
    auto ycoord =483;

    ASSERT_TRUE(item.HitTest(xcoord, ycoord)) <<
        L"hittest inside of the letter";
    ASSERT_FALSE(item.HitTest(230, 400)) <<
        L"hittest outside of the letter";
}

/// Test to ensure our game item exist.
TEST(ItemTest, Construct)
{
    Game game;
    ItemMock item(&game);
}

/// Test to ensure that setlocation works correctly.
TEST(ItemTest, GettersSetters)
{
    Game game;
    ItemMock item(&game);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second with with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);
}