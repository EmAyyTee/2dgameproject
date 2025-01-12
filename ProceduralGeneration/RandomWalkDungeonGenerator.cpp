#include "RandomWalkDungeonGenerator.h"

#include <iostream>
#include <ostream>

#include "ProceduralGenerationAlgorithms.h"
#include "Random.h"

RandomWalkDungeonGenerator::RandomWalkDungeonGenerator(TileMap & tilemap, Floor &tile)
    : visualiser(tilemap, tile), startPosition({1920/2/300,1080/2/300}) {
}


void RandomWalkDungeonGenerator::runProceduralGeneration(TileMap &map, Floor& floorTile) {
    auto floorPositions = runRandomWalk();

    std::vector positions(floorPositions.begin(), floorPositions.end());
    visualiser.paintFloorTiles(positions);

    for (const auto& position : floorPositions) {
        std::cout << "Placing tile at: (" << position.x << ", " << position.y << ")" << std::endl;
        map.setTile(position.x, position.y, floorTile);
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

