#include "Character.h"
#include "SFML/Graphics/RenderWindow.hpp"

Character::Character(const sf::Vector2f& position, sf::RenderWindow* target)
    : GameObject(position), renderTarget(target), hitPoints(1), isAlive(true) {
    animationClock.restart();
}

bool Character::manageAnimationCooldown(float duration) {
    if(isAnimationPlaying) {
        if (animationClock.getClockTime().asSeconds() >= duration) {
            animationClock.stop();
            isAnimationPlaying = false;
            return false;
        }
        return true;
    }
    animationClock.start();
    isAnimationPlaying = true;
    return true;
}


sf::RectangleShape Character::getHitBox() {
    return hitBox;
}


