#pragma once
#include "Vector2iHash.h"
#include "SFML/System/Vector2.hpp"
#include <unordered_set>

#include "TileMapVisualiser.h"

class RandomWalkDungeonGenerator {
    int iterations = 1;
    sf::Vector2i startPosition = {0, 0};
    int walkLength = 10;
    bool startRandomlyEachIteration = true;
    std::unordered_set<sf::Vector2i> dungeon;
    std::unordered_set<sf::Vector2i> floorPositions;


public:
    RandomWalkDungeonGenerator();

    void runProceduralGeneration(TileMapVisualiser& visualiser);

    std::unordered_set<sf::Vector2i> runRandomWalk();
};
