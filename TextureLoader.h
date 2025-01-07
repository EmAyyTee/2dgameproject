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

    sf::Texture playerIdleTexture;
    sf::Texture playerWalkLeft;
    sf::Texture playerWalkRight;

    // Player arrow textures

    std::vector<std::pair <int, sf::Texture>> arrowTextures;

    sf::Texture arrowUpTexture;
    sf::Texture arrowDownTexture;
    sf::Texture arrowLeftTexture;
    sf::Texture arrowRightTexture;

    //All Player Textures functions

    void loadPlayerTextures();
    void loadArrowTextures();
    void loadPlayerWalkingTextures();



    //GreenSlimeTextures
    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> greenSlimeTextures;

    sf::Texture greenSlimeIdleTexture;
    sf::Texture greenSlimeHurtTexture;
    sf::Texture greenSlimeWalkingTexture;

    //All GreenSlime textures functions

    void loadGreenSlimeTextures();

    //MainMenuTextures
    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> mainMenuPlayButtonTextures;

    sf::Texture playButton;
    sf::Texture playButtonHover;

    //All MainMenu Textures functions

    void loadMainMenuTextures();

    TextureLoader();

};