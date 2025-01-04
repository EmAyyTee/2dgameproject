#include "Player.h"

#include "Animator.h"
#include "SFML/Window/Keyboard.hpp"


Player::Player(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playerTexturesPointer,
    sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key>* supportedKeys)
    : Character(position, renderTarget), playerTexturesPointer(std::move(playerTexturesPointer)), supportedKeys(supportedKeys){

    animation.calculateTheFrames(0, 0, 128, 74);
    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;

    Character::setHitbox(sf::Vector2f{128,74}, sf::Color::Blue, position,hitBox);
}

void Player::update(float deltaTime) {
    playerGetInput();
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(playerState), sprite, playerTexturesPointer.get());
}

void Player::playerGetInput() {

    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;

    if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkUp"))) {
        direction.y -= 1.0f;
        playerState = PlayerState::PlayerWalkingRight;
    }
    if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkDown"))) {
        direction.y += 1.0f;
        playerState = PlayerState::PlayerWalkingRight;
    }
    if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkLeft"))) {
        playerState = PlayerState::PlayerWalkingLeft;
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkRight"))) {
        playerState = PlayerState::PlayerWalkingRight;
        direction.x += 1.0f;
    }
}






