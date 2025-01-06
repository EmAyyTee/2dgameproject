#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

class GameObject {
protected:
    sf::RectangleShape hitBox;
public:
    sf::Sprite sprite;
};

