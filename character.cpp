#include "character.h"
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"

character::character(const sf::Vector2f& position)
    : animation(0, 0, 128, 74), position(position) {
}

void character::draw(sf::RenderTarget& renderTarget) {
    renderTarget.draw(sprite);
}
void character::setDirection(const sf::Vector2f &direction) {
    velocity = direction*speed;
}
void character::update(float deltaTime) {
    setDirection(direction);
    position += velocity*deltaTime;
    sprite.setPosition(position);
}


