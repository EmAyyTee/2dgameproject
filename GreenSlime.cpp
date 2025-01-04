#include "GreenSlime.h"

#include <iostream>
#include <bits/fs_fwd.h>

#include "fmt/format.h"

GreenSlime::GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target)
    : Character(position, target), greenSlimeTexturesPointer(std::move(greenSlimeTexturesPointer)) {

    animation.calculateTheFrames(0,0,64,64);
    direction = {0.0f, 0.0f};
    green_slime_state = GreenSlimeState::SlimeIdle;

    hitBox.setSize(sf::Vector2f{50, 50});
    hitBox.setOutlineColor(sf::Color::Red);
    hitBox.setOutlineThickness(5.0f);
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setPosition(position);
}

void GreenSlime::update(float deltaTime, Player &player) {
    updateHitbox();
    moveTowardsPlayer(player, deltaTime);
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(green_slime_state), sprite, greenSlimeTexturesPointer.get());
}

void GreenSlime::moveTowardsPlayer(Player &player, float deltaTime) {
    directionalVector = player.position - position;
    direction = {0.0f, 0.0f};

    //Vector normalisation formula

    magnitude = sqrt(directionalVector.x * directionalVector.x + directionalVector.y * directionalVector.y);
    directionalVector.x = directionalVector.x / magnitude;
    directionalVector.y = directionalVector.y / magnitude;

    chooseAnimation();


    if (!player.sprite.getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
        position += directionalVector * speed * deltaTime;
    }
    else {
        green_slime_state = GreenSlimeState::SlimeIdle;
    }
}
void GreenSlime::updateHitbox() {
    slimeHitBox = sprite.getGlobalBounds();
    hitBox.setPosition(position);
}

void GreenSlime::draw(sf::RenderTarget &renderTarget){
    Character::draw(renderTarget);
    this -> renderTarget -> draw(hitBox);
}

void GreenSlime::chooseAnimation() {
    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
        if (directionalVector.x > 0.0f) {
            green_slime_state = GreenSlimeState::SlimeWalkRight;
            animation.calculateTheFrames(0,3,64,64);
        }
        else {
            green_slime_state = GreenSlimeState::SlimeWalkLeft;
            animation.calculateTheFrames(0,2,64,64);
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            green_slime_state = GreenSlimeState::SlimeWalkDown;
            animation.calculateTheFrames(0,0,64,64);
        }
        else {
            green_slime_state = GreenSlimeState::SlimeWalkUp;
            animation.calculateTheFrames(0,1,64,64);
        }
    }
}

