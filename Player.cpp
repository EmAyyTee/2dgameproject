#include "Player.h"

#include "Animation.h"
#include "SFML/Window/Keyboard.hpp"


Player::Player(const sf::Vector2f& position)
    : character(position) {
    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;
}

void Player::update(float deltaTime) {
    playerGetInput();
    character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(playerState));
    animation.applyToSprite(sprite);
}

void Player::playerGetInput() {

    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        playerState = PlayerState::PlayerWalkingLeft;
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerState = PlayerState::PlayerWalkingRight;
        direction.x += 1.0f;
    }
}






