#include "GreenSlime.h"

GreenSlime::GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer)
    : Character(position), greenSlimeTexturesPointer(std::move(greenSlimeTexturesPointer)) {

    animation.calculateTheFrames(0,0,64,64);
    direction = {0.0f, 0.0f};
    green_slime_state = GreenSlimeState::SlimeIdle;
}

void GreenSlime::update(float deltaTime) {
    Character::update(deltaTime);
    animation.Update(deltaTime, static_cast<int>(green_slime_state), sprite, greenSlimeTexturesPointer.get());
}

