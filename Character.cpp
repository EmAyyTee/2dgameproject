#include "Character.h"
#include "SFML/Graphics/RenderWindow.hpp"

Character::Character(const sf::Vector2f& position, sf::RenderWindow* target)
    : position(position), renderTarget(target) {
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


