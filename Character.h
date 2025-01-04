#pragma once

#include <memory>

#include "Animator.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"



class Character {
protected:
    sf::RectangleShape hitBox;
    sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
public:
    virtual ~Character() = default;

    enum class RawOfSprite {
        First = 0,
        Second = 1,
        Third = 2,
        Fourth = 3
    };

    static constexpr float speed = 200.0f;

    sf::Sprite sprite;
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2f velocity;

    Character(const sf::Vector2f& position, sf::RenderWindow* target);
    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void setDirection(const sf::Vector2f& direction);
    virtual void update(float deltaTime);
    virtual void setHitbox(sf::Vector2f size, sf::Color color, sf::Vector2f position, sf::RectangleShape &hitBox);
    virtual void updateHitBox(sf::RectangleShape &hitBox, sf::Vector2f position);
    virtual sf::RectangleShape getHitBox();

    Animator animation;
    sf::RenderWindow* renderTarget = nullptr;
};

