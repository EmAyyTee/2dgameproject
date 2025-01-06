#pragma once

#include "Animator.h"
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Character : public GameObject{
public:

    Character(const sf::Vector2f& position, sf::RenderWindow* target);

    virtual sf::RectangleShape getHitBox();

    Animator animation;
    sf::RenderWindow* renderTarget = nullptr;
};

