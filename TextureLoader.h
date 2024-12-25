#pragma once
#include <vector>

#include "SFML/Graphics/Texture.hpp"

class TextureLoader {
public:
     std::vector<sf::Texture> textures;

     sf::Texture playerIdleTexture;
     sf::Texture playerWalkLeft;
     sf::Texture playerWalkRight;

    TextureLoader();

};
