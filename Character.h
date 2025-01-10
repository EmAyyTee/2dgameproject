#pragma once

#include "Animator.h"
#include "BetterClock.h"
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Character : public GameObject{
protected:
    Animator animation;
    sf::RenderWindow* renderTarget = nullptr;

    sf::Vector2f directionalVector;
    float magnitude;

    BetterClock animationClock;
    bool isAnimationPlaying = false;
    float animationTime;

public:
    int hitPoints;

    bool isAlive;

    Character(const sf::Vector2f& position, sf::RenderWindow* target);

    bool manageAnimationCooldown(float duration);

    virtual sf::RectangleShape getHitBox();
};

