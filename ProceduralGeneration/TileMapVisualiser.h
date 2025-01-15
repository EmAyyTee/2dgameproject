#pragma once
#include <unordered_set>

#include "TileMap.h"

class TileMapVisualiser {
    TileMap tileMap, wallTileMap;
    Floor floorTile, wallTop;
    std::vector<sf::Vector2i> floorPositions;
public:

    TileMapVisualiser(TileMap& tileMap,TileMap& wallTileMap, Floor &tile, Floor &wallTile);

    void paintFloorTiles(const std::vector<sf::Vector2i>& positions);
    void paintTiles(const std::vector<sf::Vector2i>& positions, TileMap& tileMap, Floor& tile);
    void paintSingleTile(TileMap& tileMap, Floor& tile, const sf::Vector2i& position);
    void paintSingleWall(sf::Vector2i position);
};
