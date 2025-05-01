/**
 * @file Loader.h
 * @author Jackson White
 *
 * Class to load the Games we are on.
 */
 
#ifndef LOADER_H
#define LOADER_H

class Game;
#include <map>

/**
 * The loader class, used to lead specific levels of the game.
 */
class Loader {
private:
    /// The game object we have
    Game* mGame = nullptr;

    /// A map of all the declarations we have seen
    std::map<std::wstring, wxXmlNode* > mDeclarations;
public:
    Loader(Game* game);
    void LoadLevel(const std::wstring& filename);
    void XmlItem(wxXmlNode* node);
    void XmlGame(wxXmlNode* level);
    void XmlGameAnswer(wxXmlNode* node);
};

#endif //LOADER_H
