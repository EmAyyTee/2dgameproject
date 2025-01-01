#include "Player.h"

#include "Animator.h"
#include "SFML/Window/Keyboard.hpp"


Player::Player(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playerTexturesPointer)
    : Character(position), playerTexturesPointer(std::move(playerTexturesPointer)){

    animation.calculateTheFrames(0, 0, 128, 74);
    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;
}

void Player::update(float deltaTime) {
    playerGetInput();
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(playerState), sprite, playerTexturesPointer.get());
}

void Player::playerGetInput() {

    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y -= 1.0f;
        playerState = PlayerState::PlayerWalkingRight;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y += 1.0f;
        playerState = PlayerState::PlayerWalkingRight;
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






