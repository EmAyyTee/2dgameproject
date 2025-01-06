#pragma once

#include "Animator.h"
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Character : public GameObject{

public:

    Character(const sf::Vector2f& position, sf::RenderWindow* target);

    bool triggerHurtState();

    virtual sf::RectangleShape getHitBox();

    Animator animation;
    sf::RenderWindow* renderTarget = nullptr;
    bool isHurt = false;
    float hurtAnimationTimer = 0.0f;
    const float hurtAnimationDuration = 2.0f;
};

