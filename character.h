#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class character {
    public:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f velocity;
    int x = 0, y = 0;
};

