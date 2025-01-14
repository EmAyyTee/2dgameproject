#include "PlayerArrow.h"

#include <cmath>
#include <utility>

#include "GameObject.h"

PlayerArrow::PlayerArrow(sf::Vector2f position, sf::Vector2f target, std::vector<std::pair <int, sf::Texture>> *playerTexturesPointer,
                         sf::RenderWindow *renderTarget, int damage, int hp)
        :GameObject(position), renderTarget(renderTarget), arrowTextures(playerTexturesPointer), target(target), damage(damage), hp(hp) {

// Normalisation of a vector

    direction = target - position;
    hitBoxPosition = target - hitBoxPosition;

    magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude != 0) {
        directionalVector = direction / magnitude;
    } else {
        directionalVector = {0.0f, 0.0f};
    }
    directionalVector = direction / magnitude;

    setHitbox({48.0f, 5.0f}, sf::Color::Transparent, {position.x/2, position.y/2}, hitBox);
    animator.calculateTheFrames(0,0,48,48);
    animator.setNumberOfFrames(1);

}


void PlayerArrow::chooseAnimation() {
    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {

        if (directionalVector.x > 0.0f) {
            directionAnimation = ArrowDirection::Right;
            hitBox.setRotation(0.0f);
        }
        else {
            directionAnimation = ArrowDirection::Left;
            hitBox.setRotation(180.0f);
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            directionAnimation = ArrowDirection::Down;
            hitBox.setRotation(90.0f);
        }
        else {
            directionAnimation = ArrowDirection::Up;
            hitBox.setRotation(-90.0f);
        }
    }
}

void PlayerArrow::update(float deltaTime) {
    setDirection(direction);
    sprite.setPosition(position);\
    chooseAnimation();

    position += directionalVector * speed * 6.0f * deltaTime;
    animator.Update(deltaTime, static_cast<int>(directionAnimation), sprite, arrowTextures);

    hitBoxPosition = position;
    GameObject::updateHitBox(hitBox);
}

bool PlayerArrow::checkArrowLifeTime() {
    if (arrowClock.getElapsedTime().asSeconds() > maxLifetime || hp <=0)  {
        return true;
    }
    return false;
}

sf::RectangleShape &PlayerArrow::getArrowHitBox() {
    return hitBox;
}

