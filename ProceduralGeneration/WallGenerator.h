#pragma once
#include "Vector2iHash.h"
#include <unordered_set>

#include "TileMapVisualiser.h"
#include "SFML/System/Vector2.hpp"

class WallGenerator {
public:
    WallGenerator();

    static std::unordered_set<sf::Vector2i> createWalls(std::unordered_set<sf::Vector2i> floorPositions,
        TileMapVisualiser &tilemapVisualiser);

    static std::unordered_set<sf::Vector2i> findWallsInDirections(std::unordered_set<sf::Vector2i> floorPositions,
        std::vector<sf::Vector2i>directionList);
};
