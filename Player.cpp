#include "Player.h"

#include <cmath>
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

    if(canAnimationCanChange()) {
        playerState = PlayerState::PlayerIdle;
        animation.calculateTheFrames(0, 0, 128, 74);
    }

        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkUp"))) {

            if(canAnimationCanChange()) {
                direction.y -= 1.0f;
                playerState = PlayerState::PlayerWalkingRight;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkDown"))) {

            if(canAnimationCanChange()) {
                direction.y += 1.0f;
                playerState = PlayerState::PlayerWalkingRight;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkLeft"))) {

            if(canAnimationCanChange()) {
                direction.x -= 1.0f;
                playerState = PlayerState::PlayerWalkingLeft;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkRight"))) {
            if(canAnimationCanChange()) {
                direction.x += 1.0f;
                playerState = PlayerState::PlayerWalkingRight;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left ) && shotClock.getElapsedTime().asSeconds() > cooldownTimeForShootingAnArrow) {
            if(canAnimationCanChange()) {
                directionalVector = mousePosition - position;
                magnitude = sqrt(directionalVector.x * directionalVector.x + directionalVector.y * directionalVector.y);
                directionalVector = directionalVector /magnitude;

                if (playerState != PlayerState::PlayerShootingLeft || playerState != PlayerState::PlayerShootingRight) {
                    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
                        if (directionalVector.x > 0.0f) {
                            playerState = PlayerState::PlayerShootingRight;
                            animation.calculateTheFrames(0,0,128,74);
                        }
                        else {
                            playerState = PlayerState::PlayerShootingLeft;
                            animation.calculateTheFrames(0,0,128,74);
                        }
                    }else {
                        if (directionalVector.y > 0.0f) {
                            playerState = PlayerState::PlayerShootingRight;
                            animation.calculateTheFrames(0,0,128,74);
                        }
                        else {
                            playerState = PlayerState::PlayerShootingRight;
                            animation.calculateTheFrames(0,0,128,74);
                        }
                    }
                    isAnimationPlaying = true;
                    animationClock.start();
                }
            }
    }
}

bool Player::canAnimationCanChange() {
    if (isAnimationPlaying && animationClock.getClockTime().asSeconds() > 1.5f) {
        isAnimationPlaying = false;
        animationClock.restart();

        mousePosition = renderTarget->mapPixelToCoords(
          sf::Mouse::getPosition(*renderTarget));

        std::cout << mousePosition.x << ", " << mousePosition.y << std::endl;
        arrows->push_back(PlayerArrow (position, mousePosition, &playerTexturesPointer->at("arrowTextures"), renderTarget, currentDamage));
        shotClock.restart();

        return false;

    }if(isAnimationPlaying) {
        return false;
    }
    return true;
}


sf::Vector2f Player::getPosition() {
    return position;
}



