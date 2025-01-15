#include "RandomWalkDungeonGenerator.h"

#include <iostream>
#include <ostream>

#include "ProceduralGenerationAlgorithms.h"
#include "Random.h"
#include "WallGenerator.h"

RandomWalkDungeonGenerator::RandomWalkDungeonGenerator(TileMap & tilemap,TileMap& wallTileMap, Floor &tile,Floor &wallTile)
    : visualiser(tilemap,wallTileMap, tile, wallTile), startPosition({1920/2/300,1080/2/300}) {
}


void RandomWalkDungeonGenerator::runProceduralGeneration(TileMap &map,TileMap& wallTileMap, Floor &floorTile,Floor &wallTile) {
    auto floorPositions = runRandomWalk();

    std::vector positions1(floorPositions.begin(), floorPositions.end());
    visualiser.paintFloorTiles(positions1);

    for (const auto& position : floorPositions) {
        //Use for debug if something goes wrong with the gen
        // std::cout << "Placing tile at: (" << position.x << ", " << position.y << ")" << std::endl;
        map.setTile(position.x, position.y, floorTile, floorTile.getTexture());
    }
    std::unordered_set<sf::Vector2i> positions2(floorPositions.begin(), floorPositions.end());
    WallGenerator::createWalls(positions2, visualiser);

    for (const auto& position : floorPositions) {
        //Use for debug if something goes wrong with the gen
        std::cout << "Placing tile at: (" << position.x << ", " << position.y << ")" << std::endl;
        wallTileMap.setTile(position.x, position.y, wallTile, wallTile.texture);
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

