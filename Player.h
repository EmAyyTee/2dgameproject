#pragma once
#include "character.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Player : public character{
public:
    sf::Texture texture;
    sf::Sprite sprite;

    Player();
};
