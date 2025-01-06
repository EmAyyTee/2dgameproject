#include "Character.h"
#include "SFML/Graphics/RenderWindow.hpp"

Character::Character(const sf::Vector2f& position, sf::RenderWindow* target)
    : GameObject(position), renderTarget(target) {
}

bool Character::triggerHurtState() {
    if(isHurt) {
        hurtAnimationTimer += (1.0f/60.0f);
        if (hurtAnimationTimer >= hurtAnimationDuration) {
            isHurt = false;
            hurtAnimationTimer = 0.0f;
            return false;
        }
        return true;
    }
    return true;
}


sf::RectangleShape Character::getHitBox() {
    return hitBox;
}


