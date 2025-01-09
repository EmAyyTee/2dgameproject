#pragma once
#include <vector>

#include "Floor.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

class TileMap {
    float gridSizeF;
    sf::Vector2u maxSize;
    std::vector<std::vector<std::vector<Floor*>>> map;


public:

    TileMap(float gridSize, unsigned width, unsigned height);

    sf::Vector2i worldToCell(const sf::Vector2i& worldPosition);

    void update();
    void draw(sf::RenderTarget& renderTarget);
    void setTile(int gridX, int gridY, const Floor& tile);
    void removeTile();

};
