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
    hitBox.setPosition(position);
}
