#include "Floor.h"

#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"


Floor::Floor(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& textureRect)
    : isBlocked(false), isVisible(true){
    rectangle.setSize({32, 32});
    rectangle.setPosition(position);
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1.0f);

    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(position);
    sprite.setColor(sf::Color::Green);
}

Floor::Floor(const Floor &other) {
    sprite = other.sprite;
}

void Floor::update() {

}

void Floor::draw(sf::RenderTarget &renderTarget) {
    if (isVisible) {
        if (sprite.getTexture()) {
            renderTarget.draw(sprite);
        } else {
            renderTarget.draw(rectangle);
        }
    }
}

void Floor::setVisible(bool visible) {
     isVisible = visible;
}

bool Floor::getVisible() const {
    return isVisible;
}

void Floor::setBlocked(bool blocked) {
    isBlocked = blocked;
}

bool Floor::getBlocked() const {
    return isBlocked;
}

void Floor::setTexture(sf::Texture &texture, sf::IntRect textureRect) {
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
}

void Floor::setPosition(sf::Vector2f position) {
    rectangle.setPosition(position);
    sprite.setPosition(position);
}

void Floor::update(float deltaTime) {

}
