/**
 * @file LoaderTest.cpp
 * @author Aditya Menon
 * @author Jackson White
 */

#include <pch.h>
#include <Game.h>
#include <Item.h>
#include "gtest/gtest.h"
#include <wx/xml/xml.h>

using namespace std;

/// Zero level xml
const std::wstring Level0 = L"levels/level0.xml";

/// First level xml
const std::wstring Level1 = L"levels/level1.xml";

/// Second level xml
const std::wstring Level2 = L"levels/level2.xml";

/**
 * A class derived from game to check that we are loading the game correctly.
 */
class GameMock : public Game {

public:
    /**
     * Add items to the item list
     *
     * @param item The item we want to push onto the list of items.
     */
    void AddItem(std::shared_ptr<Item> item) override
    {
        mItems.push_back(item);
    }

    /**
     * Add players to the game.
     *
     * @param player The player we want to add to the game.
     */
    void AddPlayer(std::shared_ptr<Player> player) override
    {
        players.push_back(player);
    }

    /**
     * Clear all players and items from the game.
     */
    void Clear() override
    {
        mItems.clear();
        players.clear();
    }

    /**
     * Assign the loaded in answer to mAnswer.
     *
     * @param Answer the answer to assign.
     */
    void AddAnswer(shared_ptr<InvisibleAnswer> Answer) override
    {
        answer = std::move(Answer);
        for (auto item : mItems)
        {
            answer->AddGivenToSolution(item);
        }
    }

    /// List of items in the game.
    vector<std::shared_ptr<Item>> mItems;
    /// List of players in the game.
    vector<std::shared_ptr<Player>> players;
    /// Pointer to the answer for game.
    std::shared_ptr<InvisibleAnswer> answer;
};

class LoaderTesting : public ::testing::Test {
protected:
    LoaderTesting() : game(std::make_shared<GameMock>()) {}

    /// Pointer to the game object.
    std::shared_ptr<GameMock> game;
};

/**
 * Test the amount of items loaded into the game.
 */
TEST_F(LoaderTesting, AmountItemsLoadedCorrect)
{
    game->OnLoadLevel(Level1);

    ASSERT_TRUE(game->mItems.size() == 30) <<
        L"There should be 30 items in mItems";
    ASSERT_TRUE(game->players.size() == 1) <<
        L"There should only be one player item";


    game->OnLoadLevel(Level2);

    ASSERT_TRUE(game->mItems.size() == 31) <<
        L"There should be 31 items in mItems";
    ASSERT_TRUE(game->players.size() == 1) <<
        L"There should only be one player item";

    game->OnLoadLevel(Level0);

    ASSERT_TRUE(game->mItems.size() == 34) <<
        L"There should be 33 items in mItems";
    ASSERT_TRUE(game->players.size() == 1) <<
        L"There should only be one player item";
}

/**
 * Test that checks if the letters were loaded in right at the right location for level 1.
 */
TEST_F(LoaderTesting, LetterLocationsCorrect_Level1)
{
    // note that this test is only for the first level letter loco
    game->OnLoadLevel(Level1);

    // Use ids and positions from the level1 xml file to check if the letters are at the right spot
    std::map<std::string, std::pair<double, double>> expectedPositions = {
        {"i584", {16.5, 2.5}},
        {"i5ql", {5, 10}},
        {"i5wl", {6, 10}},
        {"i5el", {7, 10}},
        {"i5rl", {8, 10}},
        {"i5tl", {9, 10}},
        {"i5yl", {10, 10}},
        {"i5ul", {11, 10}},
        {"i5il", {12, 10}},
        {"i5ol", {13, 10}},
        {"i5pl", {14, 10}},
        {"i5al", {5.5, 11}},
        {"i5sl", {6.5, 11}},
        {"i5dl", {7.5, 11}},
        {"i5fl", {8.5, 11}},
        {"i5gl", {9.5, 11}},
        {"i5hl", {10.5, 11}},
        {"i5jl", {11.5, 11}},
        {"i5kl", {12.5, 11}},
        {"i5ll", {13.5, 11}},
        {"i5zl", {6, 12}},
        {"i5xl", {7, 12}},
        {"i5cl", {8, 12}},
        {"i5vl", {9, 12}},
        {"i5bl", {10, 12}},
        {"i5nl", {11, 12}},
        {"i5ml", {12, 12}},
        {"i5-l", {13, 12}},
        {"i5td", {7,4}},
    };

    // now test verify that every expected letter is loaded and at the right spot
    for (const auto& [id, pos] : expectedPositions) {
        bool found = false;
        for (const auto& item : game->mItems) {
            if (item->GetId() == id) {
                found = true;
                ASSERT_NEAR(item->GetX(), pos.first, 0.0001) << "Incorrect X for ID: " << id;
                ASSERT_NEAR(item->GetY(), pos.second, 0.0001) << "Incorrect Y for ID: " << id;
                break;
            }
        }
        ASSERT_TRUE(found) << "Letter with ID " << id << " not found in loaded items";
    }
}

/**
 * Test that checks if the letters were loaded in right at the right location for level 0.
 */
TEST_F(LoaderTesting, LetterLocationsCorrect_Level0)
{
    // note that this test is only for the first level letter loco
    game->OnLoadLevel(Level0);

    // Use ids and positions from the level1 xml file to check if the letters are at the right spot
    std::map<std::string, std::pair<double, double>> expectedPositions = {
        {"i384", {16.5, 2.5}},
        {"i3ql", {5, 10}},
        {"i3wl", {6, 10}},
        {"i3el", {7, 10}},
        {"i3rl", {8, 10}},
        {"i3tl", {9, 10}},
        {"i3yl", {10, 10}},
        {"i3ul", {11, 10}},
        {"i3il", {12, 10}},
        {"i3ol", {13, 10}},
        {"i3pl", {14, 10}},
        {"i3al", {5.5, 11}},
        {"i3sl", {6.5, 11}},
        {"i3dl", {7.5, 11}},
        {"i3fl", {8.5, 11}},
        {"i3gl", {9.5, 11}},
        {"i3hl", {10.5, 11}},
        {"i3jl", {11.5, 11}},
        {"i3kl", {12.5, 11}},
        {"i3ll", {13.5, 11}},
        {"i3zl", {6, 12}},
        {"i3xl", {7, 12}},
        {"i3cl", {8, 12}},
        {"i3vl", {9, 12}},
        {"i3bl", {10, 12}},
        {"i3nl", {11, 12}},
        {"i3ml", {12, 12}},
        {"i3-l", {13, 12}},
        {"i3sd", {7, 4}},
        {"i3pd", {8, 4}},
        {"i3rd", {10, 4}},
        {"i3td", {11, 4}},
        {"i3yd", {12, 4}},

    };

    // now test verify that every expected letter is loaded and at the right spot
    for (const auto& [id, pos] : expectedPositions) {
        bool found = false;
        for (const auto& item : game->mItems) {
            if (item->GetId() == id) {
                found = true;
                ASSERT_NEAR(item->GetX(), pos.first, 0.0001) << "Incorrect X for ID: " << id;
                ASSERT_NEAR(item->GetY(), pos.second, 0.0001) << "Incorrect Y for ID: " << id;
                break;
            }
        }
        ASSERT_TRUE(found) << "Letter with ID " << id << " not found in loaded items";
    }
}

/**
 * Test that checks if the letters were loaded in right at the right location for level 2.
 */
TEST_F(LoaderTesting, LetterLocationsCorrect_Level2)
{
    // Note that this test is only for the first level letter loco
    game->OnLoadLevel(Level2);

    // Use ids and positions from the level1 xml file to check if the letters are at the right spot
    std::map<std::string, std::pair<double, double>> expectedPositions = {
        {"i244", {4,7}},
        {"i2ql", {10, 12}},
        {"i2wl", {11, 12}},
        {"i2el", {12, 12}},
        {"i2rl", {13, 12}},
        {"i2tl", {14, 12}},
        {"i2yl", {15, 12}},
        {"i2ul", {16, 12}},
        {"i2il", {17, 12}},
        {"i2ol", {18, 12}},
        {"i2pl", {19, 12}},
        {"i2al", {10.5, 13}},
        {"i2sl", {11.5, 13}},
        {"i2dl", {12.5, 13}},
        {"i2fl", {13.5, 13}},
        {"i2gl", {14.5, 13}},
        {"i2hl", {15.5, 13}},
        {"i2jl", {16.5, 13}},
        {"i2kl", {17.5, 13}},
        {"i2ll", {18.5, 13}},
        {"i2zl", {11, 14}},
        {"i2xl", {12, 14}},
        {"i2cl", {13, 14}},
        {"i2vl", {14, 14}},
        {"i2bl", {15, 14}},
        {"i2nl", {16, 14}},
        {"i2ml", {17, 14}},
        {"i2-l", {18, 14}},
        {"i2cd", {13, 6}},
    };

    // Now test verify that every expected letter is loaded and at the right spot
    for (const auto& [id, pos] : expectedPositions) {
        bool found = false;
        for (const auto& item : game->mItems) {
            if (item->GetId() == id) {
                found = true;
                ASSERT_NEAR(item->GetX(), pos.first, 0.0001) << "Incorrect X for ID: " << id;
                ASSERT_NEAR(item->GetY(), pos.second, 0.0001) << "Incorrect Y for ID: " << id;
                break;
            }
        }
        ASSERT_TRUE(found) << "Letter with ID " << id << " not found in loaded items";
    }
}

/**
 * Test that we can parse the XML structure of a level file.
 */
TEST(LoaderTest, XmlStructure)
{
    wxXmlDocument xmlDoc;
    ASSERT_TRUE(xmlDoc.Load(L"../levels/level1.xml"));
    
    wxXmlNode* root = xmlDoc.GetRoot();
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->GetName(), "level");
    
    // Verify the level attributes
    ASSERT_TRUE(root->HasAttribute("width"));
    ASSERT_TRUE(root->HasAttribute("height"));
    ASSERT_TRUE(root->HasAttribute("tilewidth"));
    ASSERT_TRUE(root->HasAttribute("tileheight"));
    
    // Count the number of declarations
    int declarationCount = 0;
    int itemCount = 0;
    
    wxXmlNode* child = root->GetChildren();
    while (child != nullptr) {
        if (child->GetName() == "declarations")
        {
            wxXmlNode* declaration = child->GetChildren();
            while (declaration != nullptr)
            {
                declarationCount++;
                declaration = declaration->GetNext();
            }
        }
        else if (child->GetName() == "items")
        {
            wxXmlNode* item = child->GetChildren();
            while (item != nullptr)
            {
                itemCount++;
                item = item->GetNext();
            }
        }
        child = child->GetNext();
    }
    
    // There should be declarations and items in the file
    ASSERT_GT(declarationCount, 0);
    ASSERT_GT(itemCount, 0);
}

/**
 * Test that our loader can extract basic level information without loading images.
 */
TEST(LoaderTest, LevelDimensions)
{
    // This test only checks dimensions which doesn't require image loading
    wxXmlDocument xmlDoc;
    ASSERT_TRUE(xmlDoc.Load(L"../levels/level1.xml"));
    
    wxXmlNode* root = xmlDoc.GetRoot();
    int width = 0, height = 0, tileWidth = 0, tileHeight = 0;
    
    root->GetAttribute("width").ToInt(&width);
    root->GetAttribute("height").ToInt(&height);
    root->GetAttribute("tilewidth").ToInt(&tileWidth);
    root->GetAttribute("tileheight").ToInt(&tileHeight);
    
    ASSERT_EQ(width, 20);
    ASSERT_EQ(height, 15);
    ASSERT_EQ(tileWidth, 48);
    ASSERT_EQ(tileHeight, 48);
}