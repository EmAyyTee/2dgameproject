#include "Player.h"

#include "Animation.h"


Player::Player(const sf::Vector2f& position)
    : character(position) {}

void Player::update(float deltaTime) {
    character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(playerState));
    animation.applyToSprite(sprite);
}





