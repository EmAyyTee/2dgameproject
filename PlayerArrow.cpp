#include "PlayerArrow.h"

#include <cmath>
#include <utility>

#include "GameObject.h"

PlayerArrow::PlayerArrow(const sf::Vector2f &position, const sf::Vector2f &target, std::vector<std::pair <int, sf::Texture>> *playerTexturesPointer,
                         sf::RenderWindow *renderTarget)
        :GameObject(position), renderTarget(renderTarget), arrowTextures(playerTexturesPointer), target(target)
{
    animator.calculateTheFrames(0,0,48,48);
    animator.setNumberOfFrames(1);
}

void PlayerArrow::chooseAnimation(sf::Vector2f directionalVector) {
    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
        if (directionalVector.x > 0.0f) {
            direction = ArrowDirection::Right;
        }
        else {
            direction = ArrowDirection::Left;
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            direction = ArrowDirection::Down;
        }
        else {
            direction = ArrowDirection::Up;
        }
    }
}


