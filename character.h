#pragma once
#include "Animation.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"


class character {
public:
    enum class AnimationType {
        Idle = 0,
        WalkingRight = 1,
        WalkingLeft = 2,
    };

    static constexpr float speed = 100.0f;

    sf::Sprite sprite;
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2f velocity;

    character(const sf::Vector2f& position);
    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void setDirection(const sf::Vector2f& direction);
    virtual void update(float deltaTime, AnimationType animationType);
private:
    Animation animation;
};

