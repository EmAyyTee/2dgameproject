#include "RandomWalkDungeonGenerator.h"

#include <iostream>
#include <ostream>

#include "ProceduralGenerationAlgorithms.h"
#include "Random.h"


void RandomWalkDungeonGenerator::runProceduralGeneration() {
    std::unordered_set<sf::Vector2i> floorPositions = runRandomWalk();
    for (auto it : floorPositions) {
        std::cout << it.x << ", " << it.y << std::endl;
    }
}

std::unordered_set<sf::Vector2i> RandomWalkDungeonGenerator::runRandomWalk() {
    sf::Vector2i currentPostion = startPosition;
    for (int i = 0; i < iterations; i++) {
        std::unordered_set<sf::Vector2i> path = ProceduralGenerationAlgorithms::simpleRandomWalk(currentPostion, walkLength);
        floorPositions.insert(path.begin(), path.end());
        if(startRandomlyEachIteration) {
            currentPostion = Random<sf::Vector2i>::getRandomElement(floorPositions);
        }
    }
    return floorPositions;
}

