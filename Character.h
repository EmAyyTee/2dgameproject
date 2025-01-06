#pragma once

#include "Animator.h"
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Character : public GameObject{
protected:
    sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
public:

    Character(const sf::Vector2f& position, sf::RenderWindow* target);

    virtual void setDirection(const sf::Vector2f& direction);

    virtual void update(float deltaTime);



    virtual void updateHitBox(sf::RectangleShape &hitBox, sf::Vector2f position);

    virtual sf::RectangleShape getHitBox();

    Animator animation;
    sf::RenderWindow* renderTarget = nullptr;
};

