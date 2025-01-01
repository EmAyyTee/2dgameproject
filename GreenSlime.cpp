#include "GreenSlime.h"

GreenSlime::GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer)
    : Character(position), greenSlimeTexturesPointer(std::move(greenSlimeTexturesPointer)) {

    animation.calculateTheFrames(0,0,64,64);
    direction = {0.0f, 0.0f};
    green_slime_state = GreenSlimeState::SlimeIdle;
}

void GreenSlime::update(float deltaTime, Player &player) {
    moveTowardsPlayer(player);
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(green_slime_state), sprite, greenSlimeTexturesPointer.get());
}

void GreenSlime::moveTowardsPlayer(Player &player) {

    playerPosition = player.position;

    direction = {0.0f, 0.0f};
    green_slime_state = GreenSlimeState::SlimeIdle;

    if (!player.sprite.getGlobalBounds().intersects(slimeHitBox)) {
        if (position.x < playerPosition.x) {
            green_slime_state = GreenSlimeState::SlimeWalkRight;
            direction.x += 0.5f;
            animation.calculateTheFrames(0,3,64,64);
        }
        if (position.x > playerPosition.x) {
            green_slime_state = GreenSlimeState::SlimeWalkLeft;
            direction.x -= 0.5f;
            animation.calculateTheFrames(0,2,64,64);
        }
        if (position.y > playerPosition.y) {
            green_slime_state = GreenSlimeState::SlimeWalkUp;
            direction.y -= 0.5f;
            animation.calculateTheFrames(0,1,64,64);
        }
        if (position.y < playerPosition.y) {
            green_slime_state = GreenSlimeState::SlimeWalkDown;
            direction.y += 0.5f;
            animation.calculateTheFrames(0,0,64,64);
        }
    }



}


