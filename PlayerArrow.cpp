#include "PlayerArrow.h"

#include <cmath>
#include <utility>

#include "GameObject.h"

PlayerArrow::PlayerArrow(sf::Vector2f position, sf::Vector2f target, std::vector<std::pair <int, sf::Texture>> *playerTexturesPointer,
                         sf::RenderWindow *renderTarget)
        :GameObject(position), renderTarget(renderTarget), arrowTextures(playerTexturesPointer), target(target) {
    setHitbox({5.0f, 5.0f}, sf::Color::Red, {position.x-64, position.y-37}, hitBox);
    animator.calculateTheFrames(0,0,48,48);
    animator.setNumberOfFrames(1);
}

void PlayerArrow::chooseAnimation() {

    magnitude = sqrt(target.x * target.x + target.y * target.y);
    directionalVector.x = target.x / magnitude;
    directionalVector.y = target.y / magnitude;

    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
        if (directionalVector.x > 0.0f) {
            directionAnimation = ArrowDirection::Right;
        }
        else {
            directionAnimation = ArrowDirection::Left;
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            directionAnimation = ArrowDirection::Down;
        }
        else {
            directionAnimation = ArrowDirection::Up;
        }
    }
}

void PlayerArrow::update(float deltaTime) {
    GameObject::update(deltaTime);
    chooseAnimation();
    if(position != target) {
        position += directionalVector * speed * 5.0f * deltaTime;
        animator.Update(deltaTime, static_cast<int>(directionAnimation), sprite, arrowTextures);
    }
    else {
        delete this;
    }
}

