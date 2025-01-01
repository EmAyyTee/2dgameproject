#pragma once
#include <vector>

#include "SFML/Graphics/Texture.hpp"

class TextureLoader {
public:

    //int represents the number of frames that the texture has
    std::vector<std::pair <int, sf::Texture>> playerTextures;
    std::vector<std::pair <int, sf::Texture>> greenSlimeTextures;

    sf::Texture playerIdleTexture;
    sf::Texture playerWalkLeft;
    sf::Texture playerWalkRight;

    sf::Texture greenSlimeIdleTexture;

    TextureLoader();

};
