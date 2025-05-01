/**
 * @file ContainerTest.cpp
 * @author Myles Walker
 */

#include <pch.h>
#include <Game.h>
#include <Container.h>
#include <Letter.h>
#include "gtest/gtest.h"
#include <wx/xml/xml.h>

/// Letter filename closed abd front filenames
const std::wstring ContainerClosedImage = L"images/present.png";
const std::wstring ContainerFrontImage = L"images/present-front.png";
const std::wstring LetterImageName = L"images/cl.png";
/// Letter images
const std::wstring LetterAImage= L"images/al.png";
const std::wstring LetterOImage= L"images/ol.png";

/**
 * Create a container node.
 *
 * @return wxXmlNode pointer for container node.
 */
wxXmlNode* CreateContainerNode()
{
    wxXmlNode* containerNode = new wxXmlNode(wxXML_ELEMENT_NODE, "container");
    containerNode->AddAttribute("id", "i247");
    containerNode->AddAttribute("col", "23.5");
    containerNode->AddAttribute("row", "14");

    return containerNode;
}

/**
 * Create a declaration XML node for a container.
 *
 * @return wxXmlNode pointer for container declaration.
 */
wxXmlNode* CreateContainerDeclarationNode()
{
    wxXmlNode* containerDecl = new wxXmlNode(wxXML_ELEMENT_NODE, "container");
    containerDecl->AddAttribute("id", "i247");
    containerDecl->AddAttribute("width", "141");
    containerDecl->AddAttribute("height", "80");
    containerDecl->AddAttribute("image", "present.png");
    containerDecl->AddAttribute("front", "present-front.png");
    return containerDecl;
}

/// test to make sure XML loads right.
TEST(ContainerTest, XmlLoad)
{
    wxXmlNode* containerNode = CreateContainerNode();
    wxXmlNode* declarationNode = CreateContainerDeclarationNode();

    Game game;
    Container container(&game, ContainerClosedImage, ContainerFrontImage);
    container.XmlLoad(containerNode, declarationNode);

    // Verify that the container loaded its attributes correctly
    ASSERT_EQ(container.GetWidth(), 141) << L"Container width should be 141";
    ASSERT_EQ(container.GetHeight(), 80) << L"Container height should be 80";
    ASSERT_NEAR(container.GetX(), 23.5, 0.001) << L"Container x should be 23.5";
    ASSERT_NEAR(container.GetY(), 14, 0.001) << L"Container y should be 14";

    delete containerNode;
    delete declarationNode;
}

/// Test to make sure added letters works.
TEST(ContainerTest, AddLetter)
{
    wxXmlNode* containerNode = CreateContainerNode();
    wxXmlNode* declarationNode = CreateContainerDeclarationNode();

    Game game;
    Container container(&game, ContainerClosedImage, ContainerFrontImage);
    container.XmlLoad(containerNode, declarationNode);

    auto letter = std::make_shared<Letter>(&game, LetterImageName);
    ASSERT_EQ(container.GetLetters().size(), 0) << L"Container should initially be empty";

    container.AddLetter(letter);
    ASSERT_EQ(container.GetLetters().size(), 1) << L"Container should have 1 letter after adding";

    delete containerNode;
    delete declarationNode;
}

/// Test to make sure container is releasing letters right.
TEST(ContainerTest, ReleaseLetters)
{
    Game game;
    int initialCount = game.GetItemsCount();
    Container container(&game, ContainerClosedImage, ContainerFrontImage);

    auto letterA = std::make_shared<Letter>(&game, LetterAImage);
    auto letterO = std::make_shared<Letter>(&game, LetterOImage);

    container.AddLetter(letterA);
    container.AddLetter(letterO);

    ASSERT_EQ(container.GetLetters().size(), 2) << "Container should contain 2 letters before release";
    container.ReleaseLetters();

    ASSERT_EQ(game.GetItemsCount(), initialCount + 2) << "Game should have 2 additional items after releasing letters";
    ASSERT_EQ(container.GetLetters().size(), 0) << "Container should be empty after releasing letters";
}