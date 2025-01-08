#pragma once
#include <vector>

#include "Tile.h"
#include "SFML/System/Vector2.hpp"

class TileMap {
    unsigned gridSizeU;
    unsigned layers;
    float gridSizeF;
    sf::Vector2u maxSize;
    std::vector<std::vector<std::vector<Tile*>>> map;

public:

    TileMap(float gridSize, unsigned width, unsigned height);
    ~TileMap();

    void update();
    void draw(sf::RenderTarget& renderTarget);
    void addTile(const float x, const float y);
    void removeTile();
};
