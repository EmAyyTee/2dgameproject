#include "GameObject.h"

#include "SFML/Graphics/RenderTarget.hpp"

GameObject::GameObject(const sf::Vector2f &position)
    : position(position){}

void GameObject::draw(sf::RenderTarget &renderTarget) {
    renderTarget.draw(hitBox);
    renderTarget.draw(sprite);
}

void GameObject::setHitbox(sf::Vector2f size, sf::Color color, sf::Vector2f position, sf::RectangleShape &hitBox) {
    hitBox.setSize(size);
    hitBox.setOutlineColor(color);
    hitBox.setOutlineThickness(1.0f);
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setOrigin(size.x / 2, size.y / 2);
    hitBox.setPosition(position.x + sprite.getGlobalBounds().width / 2.0f, position.y + sprite.getGlobalBounds().height / 2.0f);
}
void GameObject::setHitbox(sf::Vector2f size, sf::Vector2f position, sf::RectangleShape &hitBox) {
    hitBox.setSize(size);
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setOrigin(size.x / 2, size.y / 2);
    hitBox.setPosition(position.x + sprite.getGlobalBounds().width / 2.0f, position.y + sprite.getGlobalBounds().height / 2.0f);
}

void GameObject::setDirection(const sf::Vector2f &direction) {
    velocity = direction*speed;
}

void GameObject::update(float deltaTime) {
    updateHitBox(hitBox);
    setDirection(direction);
    position += velocity*deltaTime;
    sprite.setPosition(position);
}

void GameObject::updateHitBox(sf::RectangleShape &hitBox) {
    hitBox.setPosition(position.x + positionOffset.x + sprite.getGlobalBounds().width / 2.0f, position.y + positionOffset.y + sprite.getGlobalBounds().height / 2.0f);
}
