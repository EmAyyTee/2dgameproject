#pragma once
#include <map>
#include <vector>

#include "SFML/Graphics/Texture.hpp"

class TextureLoader {
public:

    //Player textures
    //int represents the number of frames that the texture has
    std::map<std::string, std::vector<std::pair <int, sf::Texture>>> allPlayerTextures;

    std::vector<std::pair <int, sf::Texture>> playerTextures;

    sf::Texture textureLoader;

    // Player arrow textures

    std::vector<std::pair <int, sf::Texture>> arrowTextures;

    // Player shoot textures

    std::vector<std::pair <int, sf::Texture>> playerShootTextures;

    //All Player Textures functions

    void loadPlayerTextures();
    void loadArrowTextures();
    void loadPlayerWalkingTextures();
    void loadPlayerShootTextures();



    //GreenSlimeTextures
    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> greenSlimeTextures;

    //All GreenSlime textures functions

    void loadGreenSlimeTextures();

    //MainMenuTextures
    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> mainMenuPlayButtonTextures;


    //All MainMenu Textures functions

    void loadMainMenuTextures();

    TextureLoader();

};