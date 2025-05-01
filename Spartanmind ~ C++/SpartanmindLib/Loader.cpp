/**
 * @file Loader.cpp
 * @author Jackson White
 */


#include "pch.h"
#include "Loader.h"
#include "Background.h"
#include "Item.h"
#include "Container.h"
#include "Game.h"
#include "Player.h"
#include "Tray.h"
#include "ContainerAddLetterVisitor.h"
#include "Given.h"
#include "Letter.h"
#include "Obstacle.h"

using namespace std;

/**
 * Constructor for loader.
 *
 * @param game The game object.
 */
Loader::Loader(Game* game) : mGame(game)
{

}

/**
 * load level from a .xml file.
 *
 * Opens the xml file and reads the notes, creating items as appropriate.
 *
 * @param filename The xml file we are going to open.
 */
void Loader::LoadLevel(const wstring& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load the Level");
        return;
    }

    mGame->Clear();
    /// root of the xml document type level
    auto root = xmlDoc.GetRoot();
    /// check if root exists
    if (!root)
    {
        wxLogError(L"Missing <items> section");
        return;
    }

    XmlGame(root);

    auto gameNode = root->GetChildren();
    while (gameNode)
    {
        auto x = gameNode->GetName();
        if (gameNode->GetName() == L"game")
        {
            break;
        }
        gameNode = gameNode->GetNext();
    }
    if (!gameNode)
    {
        wxLogError(L"Missing <games> section");
        return;
    }

    /// we need to find the items nodes
    auto itemsNode = root->GetChildren();
    while (itemsNode)
    {
        if (itemsNode->GetName() == L"items")
        {
            break;
        }
        itemsNode = itemsNode->GetNext();

    }
    auto declaredNode = root->GetChildren();
    while (declaredNode)
    {
        if (declaredNode->GetName() == L"declarations")
        {
            break;
        }
        declaredNode = declaredNode->GetNext();
    }

    if (!itemsNode)
    {
        wxLogError(L"Missing <items> section");
        return;
    }
    if (!declaredNode)
    {
        wxLogError(L"Missing <declarations> section");
        return;
    }

    declaredNode = declaredNode->GetChildren();
    for (; declaredNode; declaredNode = declaredNode->GetNext())
    {
        mDeclarations[declaredNode->GetAttribute("id").wc_str()] = declaredNode;
    }

    /// gets the specific item
    auto item = itemsNode->GetChildren();
    for ( ; item; item = item->GetNext())
    {
        XmlItem(item);
    }

    XmlGameAnswer(gameNode);
}

/**
 * Creates the item that we are putting into the game based on information from node and declaration XML Nodes.
 *
 * @param node The item node.
 */
void Loader::XmlItem(wxXmlNode* node)
{
    /// Check they type of item
    auto type = node->GetName();

    if (type == L"letter")
    {
        /// A pointer to the item we are loading in
        shared_ptr<Item> item;
        /// The id of the item
        auto itemID = node->GetAttribute(L"id");

        /// The declared nodes
        auto i = mDeclarations.find(itemID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        /// The image name of our item
        auto itemImage = "images/" + declaredNode->GetAttribute(L"image");
        item = make_shared<Letter>(mGame, itemImage.wc_str());

        /// Add the letter item to the Game.
        mGame->AddItem(item);

        item->XmlLoad(node, declaredNode);
    }
    else if (type == L"background")
    {
        /// A pointer to the item we are loading in
        shared_ptr<Item> item;
        /// The id of the background
        auto backgroundID = node->GetAttribute(L"id");

        /// The declared nodes
        auto i = mDeclarations.find(backgroundID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        auto itemImage = "images/" + declaredNode->GetAttribute(L"image");
        item = make_shared<Background>(mGame, itemImage.wc_str());
        item->XmlLoad(node, declaredNode);

        mGame->AddItem(item);
    }
    else if (type == L"player")
    {
        /// A pointer to the item we are loading in
        shared_ptr<Player> item;
        /// The id of the item
        auto itemID = node->GetAttribute(L"id");
        /// The declared nodes
        auto i = mDeclarations.find(itemID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        /// The image name of our item
        auto playerImage1 = "images/" + declaredNode->GetAttribute(L"image1");
        auto playerImage2 = "images/" + declaredNode->GetAttribute(L"image2");

        item = make_shared<Player>(mGame, mGame->Level(), playerImage1.wc_str(), playerImage2.wc_str());
        mGame->AddPlayer(item);
        item->XmlLoad(node, declaredNode);
    }
    else if (type == L"tray")
    {
        shared_ptr<Item> item;
        /// The id of the background
        auto trayID = node->GetAttribute(L"id");

        /// The declared nodes
        auto i = mDeclarations.find(trayID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        auto itemImage = "images/" + declaredNode->GetAttribute(L"image");
        item = make_shared<Tray>(mGame, itemImage.wc_str());
        mGame->AddItem(item);
        item->XmlLoad(node, declaredNode);
    }
    else if (type == L"given")
    {
        /// A pointer to the item we are loading in
        shared_ptr<Item> item;
        /// The id of the item
        auto itemID = node->GetAttribute(L"id");

        /// The declared nodes
        auto i = mDeclarations.find(itemID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        /// The image name of our item
        auto itemImage = "images/" + declaredNode->GetAttribute(L"image");
        item = make_shared<Given>(mGame, itemImage.wc_str());

        /// Add the letter item to the Game.
        mGame->AddItem(item);

        item->XmlLoad(node, declaredNode);
    }

    else if (type == L"container")
    {
        /// A pointer to the item we are loading in
        shared_ptr<Item> item;
        /// The id of the item
        auto itemID = node->GetAttribute(L"id");

        /// The declared nodes
        auto i = mDeclarations.find(itemID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        /// The image name of our item
        auto containerImage = "images/" + declaredNode->GetAttribute(L"image");
        auto frontImage = "images/" + declaredNode->GetAttribute(L"front");

        item = make_shared<Container>(mGame, containerImage.wc_str(), frontImage.wc_str());
        /// Add the letter item to the Game.
        mGame->AddItem(item);
        item->XmlLoad(node, declaredNode);

        auto letterNode = node->GetChildren();
        for ( ; letterNode; letterNode = letterNode->GetNext())
        {
            /// A pointer to the item we are loading in
            shared_ptr<Item> letter;
            /// the id of the item
            auto itemID = letterNode->GetAttribute(L"id");

            /// The declared nodes
            auto i = mDeclarations.find(itemID.wc_str());
            if (i == mDeclarations.end())
            {
                wxLogError(L"Missing declarations section");
                return;
            }

            auto declaredNodeTwo = i->second;

            /// The image name of our item
            auto itemImage = "images/" + declaredNodeTwo->GetAttribute(L"image");
            /// Since these are duplicate letters, we need to create them
            auto newLetter = std::make_shared<Letter>(mGame, itemImage.wc_str());
            newLetter->XmlLoad(letterNode, declaredNodeTwo);
            ContainerAddLetterVisitor containerAdd(newLetter);
            item->Accept(&containerAdd);
        }
    }
    else if (type == L"obstacle")
    {
        /// A pointer to the item we are loading in
        shared_ptr<Item> item;
        /// The id of the background
        auto backgroundID = node->GetAttribute(L"id");

        /// The declared nodes
        auto i = mDeclarations.find(backgroundID.wc_str());
        if (i == mDeclarations.end())
        {
            wxLogError(L"Missing declarations section");
            return;
        }

        auto declaredNode = i->second;

        auto itemImage = "images/" + declaredNode->GetAttribute(L"image");
        item = make_shared<Obstacle>(mGame, itemImage.wc_str());
        item->XmlLoad(node, declaredNode);

        mGame->AddItem(item);
    }
}

/**
 * Load the game.
 * @param level The level to load the game from.
 */
void Loader::XmlGame(wxXmlNode* level)
{
    mGame->XmlGame(level);
}

/**
 * Loads the answer to the game.
 * @param node The node with the answer to the game.
 */
void Loader::XmlGameAnswer(wxXmlNode* node)
{
    auto answer = make_shared<InvisibleAnswer>();
    answer->XmlLoad(node);
    mGame->AddAnswer(answer);
}