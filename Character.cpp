#include "Character.h"
#include "SFML/Graphics/RenderWindow.hpp"

Character::Character(const sf::Vector2f& position, sf::RenderWindow* target)
    : GameObject(position), renderTarget(target) {
}

void Character::setDirection(const sf::Vector2f &direction) {
    velocity = direction*speed;
}
void Character::update(float deltaTime) {
    updateHitBox(hitBox, position);
    setDirection(direction);
    position += velocity*deltaTime;
    sprite.setPosition(position);
}

void Character::setHitbox(sf::Vector2f size, sf::Color color, sf::Vector2f position, sf::RectangleShape &hitBox) {
    hitBox.setSize(size);
    hitBox.setOutlineColor(color);
    hitBox.setOutlineThickness(1.0f);
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setPosition(position);
}

void Character::updateHitBox(sf::RectangleShape &hitBox, sf::Vector2f position) {
    hitBox.setPosition(position);
}

sf::RectangleShape Character::getHitBox() {
    return hitBox;
}


