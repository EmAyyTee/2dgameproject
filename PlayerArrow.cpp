#include "PlayerArrow.h"

#include <cmath>
#include <utility>

#include "GameObject.h"

PlayerArrow::PlayerArrow(sf::Vector2f position, sf::Vector2f target, std::vector<std::pair <int, sf::Texture>> *playerTexturesPointer,
                         sf::RenderWindow *renderTarget)
        :GameObject(position), renderTarget(renderTarget), arrowTextures(playerTexturesPointer), target(target) {

    setHitbox({5.0f, 5.0f}, sf::Color::Red, {position.x, position.y}, hitBox);
    animator.calculateTheFrames(0,0,48,48);
    animator.setNumberOfFrames(1);

// Normalisation of a vector

    direction = target - position;

    magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude != 0) {
        directionalVector = direction / magnitude;
    } else {
        directionalVector = {0.0f, 0.0f};
    }
    directionalVector = direction / magnitude;
}

void PlayerArrow::chooseAnimation() {
    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {

        if (directionalVector.x > 0.0f) {
            directionAnimation = ArrowDirection::Right;
            hitBoxPosition = sf::Vector2f{position.x + sprite.getGlobalBounds().width, position.y + sprite.getGlobalBounds().height/2};
        }
        else {
            directionAnimation = ArrowDirection::Left;
            hitBoxPosition = sf::Vector2f{position.x + sprite.getGlobalBounds().width/8, position.y + sprite.getGlobalBounds().height/2};
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            directionAnimation = ArrowDirection::Down;
            hitBoxPosition = sf::Vector2f{position.x + sprite.getGlobalBounds().width/2, position.y + sprite.getGlobalBounds().height};
        }
        else {
            directionAnimation = ArrowDirection::Up;
            hitBoxPosition = sf::Vector2f{position.x + sprite.getGlobalBounds().width/2, position.y};
        }
    }
}

void PlayerArrow::update(float deltaTime,sf::Vector2f shiftOfHitBoxPos) {
    setDirection(direction);
    sprite.setPosition(position);
    GameObject::updateHitBox(hitBox, hitBoxPosition);
    chooseAnimation();

    position += directionalVector * speed * 6.0f * deltaTime;
    animator.Update(deltaTime, static_cast<int>(directionAnimation), sprite, arrowTextures);
}

bool PlayerArrow::checkArrowLifeTime() {
    if (arrowClock.getElapsedTime().asSeconds() > maxLifetime) {
        return true;
    }
    return false;
}

sf::RectangleShape &PlayerArrow::getArrowHitBox() {
    return hitBox;
}

