#include "Floor.h"
#include "SFML/Graphics/RenderTarget.hpp"


Floor::Floor(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& textureRect)
    : isBlocked(false), isVisible(true){
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(position);
}

Floor::Floor(const Floor &other) {
    sprite = other.sprite;
}

void Floor::update() {

}

void Floor::draw(sf::RenderTarget &renderTarget) {
    if(isVisible) {
        renderTarget.draw(sprite);
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
    sprite.setPosition(position);
}

void Floor::update(float deltaTime) {

}
