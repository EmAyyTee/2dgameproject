#pragma once
#include "TileMap.h"

class TileMapVisualiser {
    TileMap tileMap;
    Floor floorTile;
    std::vector<sf::Vector2i> floorPositions;
public:

    TileMapVisualiser(TileMap& tileMap, Floor &tile);

    void paintFloorTiles(const std::vector<sf::Vector2i>& positions);
    void paintTiles(const std::vector<sf::Vector2i>& positions, TileMap& tileMap, const Floor& tile);
    void paintSingleTile(TileMap& tileMap, const Floor& tile, const sf::Vector2i& position);
};
