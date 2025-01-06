#include "Character.h"
#include "SFML/Graphics/RenderWindow.hpp"

Character::Character(const sf::Vector2f& position, sf::RenderWindow* target)
    : GameObject(position), renderTarget(target) {
}

sf::RectangleShape Character::getHitBox() {
    return hitBox;
}


