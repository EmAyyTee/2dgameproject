#pragma once
#include "Animation.h"
#include "SFML/Graphics/Sprite.hpp"



class Character {
protected:
    sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
public:

    static constexpr float speed = 100.0f;

    sf::Sprite sprite;
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2f velocity;

    Character(const sf::Vector2f& position);
    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void setDirection(const sf::Vector2f& direction);
    virtual void update(float deltaTime);

    Animation animation;
};

