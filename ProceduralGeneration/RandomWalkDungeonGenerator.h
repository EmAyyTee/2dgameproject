#pragma once
#include "Vector2iHash.h"
#include "SFML/System/Vector2.hpp"
#include <unordered_set>

#include "TileMapVisualiser.h"

class RandomWalkDungeonGenerator {
    int iterations = 10;
    sf::Vector2i startPosition;
    int walkLength = 5;
    bool startRandomlyEachIteration = true;
    std::unordered_set<sf::Vector2i> dungeon;
    std::unordered_set<sf::Vector2i> floorPositions;
    TileMapVisualiser visualiser;



public:
    RandomWalkDungeonGenerator(TileMap &tilemap, Floor &tile);

    void runProceduralGeneration(TileMap &map, Floor& floorTile);

    std::unordered_set<sf::Vector2i> runRandomWalk();


};
