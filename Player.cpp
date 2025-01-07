#include "Player.h"

#include <iostream>

#include "Animator.h"
#include "PlayerArrow.h"
#include "fmt/core.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"


Player::Player(const sf::Vector2f& position, std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer,
    sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key>* supportedKeys)
    : Character(position, renderTarget), playerTexturesPointer(std::move(playerTexturesPointer)), supportedKeys(supportedKeys), currentDamage(1){

    animation.calculateTheFrames(0, 0, 128, 74);
    animation.setNumberOfFrames(6);
    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;

    Character::setHitbox(sf::Vector2f(128.0f, 74.0f), sf::Color::Blue, position,hitBox);
}

void Player::update(float deltaTime, std::vector<PlayerArrow> &arrows) {
    this -> arrows = &arrows;
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left ) && shotClock.getElapsedTime().asSeconds() > cooldownTimeForShootingAnArrow) {
        mousePosition = renderTarget->mapPixelToCoords(
       sf::Mouse::getPosition(*renderTarget)
   );
        std::cout << mousePosition.x << ", " << mousePosition.y << std::endl;
        arrows->push_back(PlayerArrow (position, mousePosition, &playerTexturesPointer->at("arrowTextures"), renderTarget, currentDamage));
        shotClock.restart();
    }
}

sf::Vector2f Player::getPosition() {
    return position;
}





