#pragma once
#include "SFML/Graphics/RectangleShape.hpp"

class Tile {
protected:
    sf::RectangleShape shape;
public:
    Tile(float x, float y,float gridSizeF);
    Tile();

    void update();

    void draw(sf::RenderTarget& renderTarget);
};
