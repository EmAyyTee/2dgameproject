#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Floor {
protected:
    sf::RectangleShape rectangle;
    sf::Sprite sprite;
    bool isBlocked;
    bool isVisible;
public:
    Floor(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& textureRect);

    Floor(const Floor& other);

    void update();

    void draw(sf::RenderTarget& renderTarget);

    void setVisible(bool visible);

    bool getVisible() const;

    void setBlocked(bool blocked);

    bool getBlocked() const;

    void setTexture(sf::Texture& texture, sf::IntRect textureRect);

    void setPosition(sf::Vector2f position);

    void update(float deltaTime);
};
