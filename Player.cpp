#include "Player.h"

#include <cmath>

#include "Animator.h"
#include "PlayerArrow.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"


Player::Player(const sf::Vector2f& position, std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer,
    sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key>* supportedKeys)
    : Character(position, renderTarget), playerTexturesPointer(std::move(playerTexturesPointer)), supportedKeys(supportedKeys){

    animation.calculateTheFrames(0, 0, 128, 74);
    animation.setNumberOfFrames(6);
    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;

    Character::setHitbox(sf::Vector2f{128,74}, sf::Color::Blue, position,hitBox);
}

void Player::update(float deltaTime) {
    playerGetInput();
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(playerState), sprite, &playerTexturesPointer->at("playerTextures"));
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        directionalVector = sf::Vector2f(renderTarget->mapPixelToCoords(sf::Mouse::getPosition(*renderTarget))) - position;

        magnitude = std::sqrt(directionalVector.x * directionalVector.x + directionalVector.y * directionalVector.y);
        directionalVector.x = directionalVector.x / magnitude;
        directionalVector.y = directionalVector.y / magnitude;

        PlayerArrow arrow(position, directionalVector,&playerTexturesPointer->at("arrowTextures"), renderTarget);

    }
}

sf::Vector2f Player::getPosition() {
    return position;
}





