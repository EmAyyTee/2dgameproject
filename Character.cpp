#include "Character.h"
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"

Character::Character(const sf::Vector2f& position)
    : animation(0, 0, 128, 74), position(position) {
}

void Character::draw(sf::RenderTarget& renderTarget) {
    renderTarget.draw(sprite);
}
void Character::setDirection(const sf::Vector2f &direction) {
    velocity = direction*speed;
}
void Character::update(float deltaTime) {
    setDirection(direction);
    position += velocity*deltaTime;
    sprite.setPosition(position);
}


