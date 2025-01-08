#pragma once
#include "Vector2iHash.h"
#include "SFML/System/Vector2.hpp"
#include <unordered_set>

class RandomWalkDungeonGenerator {
    int iterations = 10;
    sf::Vector2i startPosition = {0, 0};
    int walkLength = 10;
    bool startRandomlyEachIteration = true;
    std::unordered_set<sf::Vector2i> dungeon;
    std::unordered_set<sf::Vector2i> floorPositions;

public:
    RandomWalkDungeonGenerator() = default;

    void runProceduralGeneration();

    std::unordered_set<sf::Vector2i> runRandomWalk();
};