#include "Player.h"

#include <utility>

#include "SFML/Graphics/RenderWindow.hpp"

Player::Player() {
    texture.loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png");
    sprite.setTextureRect(sf::IntRect(x, y, 128, 74));
    sprite.setTexture(texture);
}


