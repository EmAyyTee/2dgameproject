#include "GreenSlime.h"
#include <iostream>

#include "fmt/format.h"

GreenSlime::GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target)
    : Character(position, target), greenSlimeTexturesPointer(std::move(greenSlimeTexturesPointer)) {
    animation.calculateTheFrames(0,0,64,64);
    animation.setNumberOfFrames(6);
    direction = {0.0f, 0.0f};
    green_slime_animation = GreenSlimeAnimation::SlimeIdle;

    Character::setHitbox(sf::Vector2f{17.0f,15.0f}, sf::Color::Red, position, hitBox);
    Character::setHitbox(sf::Vector2f{464.0f,464.0f}, sf::Color::Green, position, detectionHitBox);
    Character::setHitbox(sf::Vector2f{64.0f,64.0f}, sf::Color::Magenta, position, attackHitbox);
}

void GreenSlime::update(float deltaTime, Player &player) {
    checkForThePlayer(player);
    moveTowardsPlayer(player, deltaTime);
    checkForTheDamage(player);
    Character::update(deltaTime);
    Character::updateHitBox(detectionHitBox);
    Character::updateHitBox(attackHitbox);
    animation.Update(deltaTime, static_cast<int>(green_slime_animation), sprite, greenSlimeTexturesPointer.get());
}


void GreenSlime::checkForThePlayer(Player &player) {
    if (player.getHitBox().getGlobalBounds().intersects(detectionHitBox.getGlobalBounds())) {
        green_slime_detection = GreenSlimeDetection::PlayerDetected;
    }
}

void GreenSlime::checkForTheDamage(Player &player) {
    for (PlayerArrow &arrow : *player.arrows) {
        if (arrow.getArrowHitBox().getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
            if (green_slime_animation != GreenSlimeAnimation::SlimeHurt) {
                green_slime_animation = GreenSlimeAnimation::SlimeHurt;
                isAnimationPlaying = true;
                animationClock.start();
            }
        }
    }
    if (isAnimationPlaying && animationClock.getClockTime().asSeconds() > 0.5f) {
        std::cout << "This is true" << std::endl;
        green_slime_animation = GreenSlimeAnimation::SlimeIdle;
        isAnimationPlaying = false;
        animationClock.restart();
    }
}

void GreenSlime::moveTowardsPlayer(Player &player, float deltaTime) {
    directionalVector = player.getPosition() - position;
    direction = {0.0f, 0.0f};

    //Vector normalisation formula

    magnitude = sqrt(directionalVector.x * directionalVector.x + directionalVector.y * directionalVector.y);
    directionalVector.x = directionalVector.x / magnitude;
    directionalVector.y = directionalVector.y / magnitude;

    if (green_slime_detection == GreenSlimeDetection::PlayerDetected){
        if(!isAnimationPlaying) {
            chooseAnimation();
        }

        if (!player.getHitBox().getGlobalBounds().intersects(attackHitbox.getGlobalBounds()) && !isAnimationPlaying) {
            position += directionalVector * speed * deltaTime;
        }
        else {
            if(!isAnimationPlaying) {
                green_slime_animation = GreenSlimeAnimation::SlimeIdle;
            }
        }
    }
}

void GreenSlime::chooseAnimation() {
    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
        if (directionalVector.x > 0.0f) {
            green_slime_animation = GreenSlimeAnimation::SlimeWalkRight;
            animation.calculateTheFrames(0,3,64,64);
        }
        else {
            green_slime_animation = GreenSlimeAnimation::SlimeWalkLeft;
            animation.calculateTheFrames(0,2,64,64);
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            green_slime_animation = GreenSlimeAnimation::SlimeWalkDown;
            animation.calculateTheFrames(0,0,64,64);
        }
        else {
            green_slime_animation = GreenSlimeAnimation::SlimeWalkUp;
            animation.calculateTheFrames(0,1,64,64);
        }
    }
}

void GreenSlime::draw(sf::RenderTarget &renderTarget) {
    Character::draw(renderTarget);
    renderTarget.draw(detectionHitBox);
    renderTarget.draw(attackHitbox);
}
