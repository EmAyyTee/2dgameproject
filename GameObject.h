#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

class GameObject {
protected:

    static constexpr float speed = 200.0f;
    sf::RectangleShape hitBox;
    sf::Vector2f position;

    GameObject(const sf::Vector2f& position);

public:
    virtual ~GameObject() = default;

    sf::Vector2f velocity;

    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& renderTarget);

    virtual void setHitbox(sf::Vector2f size, sf::Color color, sf::Vector2f position, sf::RectangleShape &hitBox);
};

