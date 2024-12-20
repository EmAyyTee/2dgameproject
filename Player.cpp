#include "Player.h"

#include <utility>

#include "SFML/Graphics/RenderWindow.hpp"

Player::Player() {
    texture.loadFromFile("PlayerCharacter/Archer/Idle1.png");
    sprite.setTexture(texture);
}


