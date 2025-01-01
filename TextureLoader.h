#pragma once
#include <vector>

#include "SFML/Graphics/Texture.hpp"

class TextureLoader {
public:

    //Player textures
    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> playerTextures;

    sf::Texture playerIdleTexture;
    sf::Texture playerWalkLeft;
    sf::Texture playerWalkRight;


    //GreenSlimeTextures
    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> greenSlimeTextures;

    sf::Texture greenSlimeIdleTexture;
    sf::Texture greenSlimeWalkingTexture;


    TextureLoader();

};
