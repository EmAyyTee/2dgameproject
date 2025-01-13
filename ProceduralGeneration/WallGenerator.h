#pragma once
#include <unordered_set>

#include "TileMapVisualiser.h"
#include "SFML/System/Vector2.hpp"

class WallGenerator {
public:
    static void createWalls(std::unordered_set<sf::Vector2i> floorPositions, TileMapVisualiser tileMapVisualiser);

    static sf::Vector2i findWallsInDirections(std::unordered_set<sf::Vector2i> floorPositions, sf::Vector2i directionsList);

    static std::unordered_set<sf::Vector2i> wallPositions;

    static std::unordered_set<sf::Vector2i> basicWallPositions;
};
