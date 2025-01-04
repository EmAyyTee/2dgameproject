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
    moveTowardsPlayer(player);
    Character::update(deltaTime);
    std::cout << "The slime's state is: " << static_cast<int>(green_slime_state) << "\n";
    animation.Update(deltaTime, static_cast<int>(green_slime_state), sprite, greenSlimeTexturesPointer.get());
}

void GreenSlime::moveTowardsPlayer(Player &player) {
    playerPosition = player.position;
    direction = {0.0f, 0.0f};

    if (!player.sprite.getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
        if (position.x < playerPosition.x+32 && (position.y < playerPosition.y+64 || position.y > playerPosition.y-64)) {
            // green_slime_state = GreenSlimeState::SlimeWalkRight;
            direction.x += 0.5f;
            animation.calculateTheFrames(0,3,64,64);
        }
        if (position.x > playerPosition.x+32){
            // green_slime_state = GreenSlimeState::SlimeWalkLeft;
            direction.x -= 0.5f;
            animation.calculateTheFrames(0,2,64,64);
        }
        if (position.y > playerPosition.y+14) {
            // green_slime_state = GreenSlimeState::SlimeWalkUp;
            direction.y -= 0.5f;
            animation.calculateTheFrames(0,1,64,64);
        }
        if (position.y < playerPosition.y+14) {
            // green_slime_state = GreenSlimeState::SlimeWalkDown;
            direction.y += 0.5f;
            animation.calculateTheFrames(0,0,64,64);
        }
    } else {
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
