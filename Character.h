#pragma once

#include "Animator.h"
#include "BetterClock.h"
#include "GameObject.h"
#include "fmt/chrono.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Character : public GameObject{
protected:
    Animator animation;
    sf::RenderWindow* renderTarget = nullptr;

    BetterClock animationClock;
    bool isAnimationPlaying = false;

public:

    Character(const sf::Vector2f& position, sf::RenderWindow* target);

    bool manageAnimationCooldown(float duration);

    virtual sf::RectangleShape getHitBox();
};

