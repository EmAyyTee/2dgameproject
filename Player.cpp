#include "Player.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include "Animator.h"
#include "PlayerArrow.h"
#include "fmt/core.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"


Player::Player(const sf::Vector2f& position, std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer,
    sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key>* supportedKeys)
    : Character(position, renderTarget), playerTexturesPointer(std::move(playerTexturesPointer)),
supportedKeys(supportedKeys), currentDamage(1), arrowsHp(1){

    hitPoints = 30;
    animation.calculateTheFrames(0, 0, 128, 74);
    animation.setNumberOfFrames(6);
    direction = {0.0f, 0.0f};
    playerState = PlayerState::PlayerIdle;
    positionOffset = {0.0f, 20.0f};

    Character::setHitbox(sf::Vector2f(40.0f, 38.0f), sf::Color::Transparent, position,hitBox);
    Character::setHitbox(sf::Vector2f(128.0f, 128.0f), sf::Color::Transparent, position,detectionHitbox);
}

void Player::update(float deltaTime, std::vector<PlayerArrow> &arrows) {
    this -> arrows = &arrows;
    playerGetInput();
    GameObject::updateHitBox(detectionHitbox);
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(playerState), sprite, &playerTexturesPointer->at("playerTextures"));
}

void Player::playerGetInput() {

    direction = (sf::Vector2f{0.0f, 0.0f} + tempDirection);

    if(canAnimationCanChange()) {
        playerState = PlayerState::PlayerIdle;
        animation.calculateTheFrames(0, 0, 128, 74);
    }

        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkUp"))) {

            if(canAnimationCanChange()) {
                direction.y -= 1.0f * speedModifier ;
                playerState = PlayerState::PlayerWalkingRight;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkDown"))) {

            if(canAnimationCanChange()) {
                direction.y += 1.0f * speedModifier ;
                playerState = PlayerState::PlayerWalkingRight;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkLeft"))) {

            if(canAnimationCanChange()) {
                direction.x -= 1.0f * speedModifier ;
                playerState = PlayerState::PlayerWalkingLeft;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }
        if (sf::Keyboard::isKeyPressed(supportedKeys->at("walkRight"))) {
            if(canAnimationCanChange()) {
                direction.x += 1.0f * speedModifier ;
                playerState = PlayerState::PlayerWalkingRight;
                animation.calculateTheFrames(0, 0, 128, 74);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left ) && shotClock.getElapsedTime().asSeconds() > cooldownTimeForShootingAnArrow) {
            directionalVector = mousePosition - position;
            magnitude = sqrt(directionalVector.x * directionalVector.x + directionalVector.y * directionalVector.y);
            directionalVector = directionalVector /magnitude;

            mousePosition = renderTarget->mapPixelToCoords(sf::Mouse::getPosition(*renderTarget));
            isShooting = true;

            if(canAnimationCanChange()) {
                if (playerState != PlayerState::PlayerShootingLeft
                    || playerState != PlayerState::PlayerShootingRight) {
                    //Logic for when I have sprites for up and down

                    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
                        if (directionalVector.x > 0.0f) {
                            playerState = PlayerState::PlayerShootingRight;
                        }
                        else {
                            playerState = PlayerState::PlayerShootingLeft;
                        }
                    }else {
                        if (directionalVector.y > 0.0f){
                            if (playerState == PlayerState::PlayerIdle) {
                                playerState = PlayerState::PlayerShootingRight;
                            }else if (playerState == PlayerState::PlayerWalkingRight) {
                                playerState = PlayerState::PlayerShootingRight;
                            }
                            else if ( playerState == PlayerState::PlayerWalkingLeft ) {
                                playerState = PlayerState::PlayerShootingLeft;
                            }
                        }
                        else {
                            if (playerState == PlayerState::PlayerIdle) {
                                playerState = PlayerState::PlayerShootingRight;
                            }else if (playerState == PlayerState::PlayerWalkingRight) {
                                playerState = PlayerState::PlayerShootingRight;
                            }
                            else if ( playerState == PlayerState::PlayerWalkingLeft ) {
                                playerState = PlayerState::PlayerShootingLeft;
                            }
                        }

                    }
                    animation.calculateTheFrames(0,0,128,74);
                    isAnimationPlaying = true;
                    animation.setHoldTime(0.05f);
                    animationTime = 0.75f;
                    animationClock.start();

                }
            }
        }else if (playerDashAbility >= 2) {
            if (sf::Keyboard::isKeyPressed(supportedKeys->at("dash"))
                && dashClock.getElapsedTime().asSeconds() > cooldownTimeForDashing) {
                dashClock.restart();
                if(canAnimationCanChange()) {
                    tempDirection += direction * 2.0f;
                    if (playerState == PlayerState::PlayerWalkingRight) {
                        playerState = PlayerState::PlayerDashingRight;
                    } else if (playerState == PlayerState::PlayerWalkingLeft) {
                        playerState = PlayerState::PlayerDashingLeft;
                    }
                    animation.calculateTheFrames(0, 0, 128, 74);
                    isAnimationPlaying = true;
                    animation.setHoldTime(0.15f);
                    animationTime = 0.5f;
                    animationClock.start();
                }
            }
        }
}

bool Player::canAnimationCanChange() {
    if (isAnimationPlaying && animationClock.getClockTime().asSeconds() > animationTime && !isHurt) {
        isAnimationPlaying = false;
        animation.setHoldTime(0.1f);
        animationClock.restart();

        if (isShooting) {
            arrows->emplace_back(position, mousePosition, &playerTexturesPointer->at("arrowTextures"), renderTarget, currentDamage, arrowsHp);
            shotClock.restart();
            isShooting = false;
        } else if (tempDirection != sf::Vector2f{0.0f, 0.0f}) {
            tempDirection = sf::Vector2f{0.0f, 0.0f};
        }

        return false;

    }if(isAnimationPlaying) {
        return false;
    }
    return true;
}



sf::Vector2f Player::getPosition() {
    return position;
}

void Player::setPosition(sf::Vector2f position) {
    this -> position = position;
}

void Player::addToScore(int points) {
    score += points;
}


sf::RectangleShape Player::getPlayerHitBox() {
    return detectionHitbox;
}

void Player::draw(sf::RenderTarget &renderTarget) {
    Character::draw(renderTarget);
    renderTarget.draw(detectionHitbox);
}

void Player::getDamage(int damage) {
    hitPoints -= damage;
    if(playerState != PlayerState::PlayerHurt && !isAnimationPlaying) {
        playerState = PlayerState::PlayerHurt;
        animation.calculateTheFrames(0,0,128,74);
        isAnimationPlaying = true;
        animation.setHoldTime(0.1f);
        animationTime = 0.25f;
        animationClock.start();
        isHurt = true;
    }
    if (isAnimationPlaying && animationClock.getClockTime().asSeconds() > animationTime || hitPoints < 0) {
        isAnimationPlaying = false;
        animation.setHoldTime(0.1f);
        animationClock.restart();
        std::cout << "I took " << damage << " points of damage!" << "\n";
        isHurt = false;
    }
}

bool Player::canThePlayerLevelUp() {

    int a = 2, b = 2, next = 0;

    for (int i = 0; i < playerLevel; i++) {
        next = a+b;
        a = b;
        b = next;
    }

    if (score >= next) {
        playerLevel++;
        return true;
    }
    return false;
}


void Player::saveToFile(std::ofstream &file) {

    //saving pos

    file.write(reinterpret_cast<const char *>(&position.x), sizeof(position.x));
    file.write(reinterpret_cast<const char *>(&position.y), sizeof(position.y));

    //saving hp

    file.write(reinterpret_cast<const char *>(&hitPoints), sizeof(hitPoints));
    file.write(reinterpret_cast<const char *>(&playerHealthLevel), sizeof(playerHealthLevel));

    //Saving dmg

    file.write(reinterpret_cast<const char *>(&currentDamage), sizeof(currentDamage));
    file.write(reinterpret_cast<const char *>(&playerLevel), sizeof(playerLevel));
    file.write(reinterpret_cast<const char *>(&playerPiercingLevel), sizeof(playerPiercingLevel));
    file.write(reinterpret_cast<const char *>(&playerDamageLevel), sizeof(playerDamageLevel));
    file.write(reinterpret_cast<const char *>(&playerSpeedLevel), sizeof(playerSpeedLevel));
    file.write(reinterpret_cast<const char *>(&speedModifier), sizeof(speedModifier));
    file.write(reinterpret_cast<const char *>(&playerDashAbility), sizeof(playerDashAbility));
    file.write(reinterpret_cast<const char *>(&score), sizeof(score));
    file.write(reinterpret_cast<const char *>(&arrowsHp), sizeof(arrowsHp));
}

void Player::loadFromFile(std::ifstream &file) {

    //Loading pos

    file.read(reinterpret_cast<char *>(&position.x), sizeof(position.x));
    file.read(reinterpret_cast<char *>(&position.y), sizeof(position.y));

    //Loading hp

    file.read(reinterpret_cast<char *>(&hitPoints), sizeof(hitPoints));
    file.read(reinterpret_cast<char *>(&playerHealthLevel), sizeof(playerHealthLevel));

    //Loading dmg

    file.read(reinterpret_cast<char *>(&currentDamage), sizeof(currentDamage));
    file.read(reinterpret_cast<char *>(&playerLevel), sizeof(playerLevel));
    file.read(reinterpret_cast<char *>(&playerPiercingLevel), sizeof(playerPiercingLevel));
    file.read(reinterpret_cast<char *>(&playerDamageLevel), sizeof(playerDamageLevel));
    file.read(reinterpret_cast<char *>(&playerSpeedLevel), sizeof(playerSpeedLevel));
    file.read(reinterpret_cast<char *>(&speedModifier), sizeof(speedModifier));
    file.read(reinterpret_cast<char *>(&playerDashAbility), sizeof(playerDashAbility));
    file.read(reinterpret_cast<char *>(&score), sizeof(score));
    file.read(reinterpret_cast<char *>(&arrowsHp), sizeof(arrowsHp));
}

