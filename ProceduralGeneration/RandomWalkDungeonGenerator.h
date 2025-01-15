#pragma once
#include "Vector2iHash.h"
#include "SFML/System/Vector2.hpp"
#include <unordered_set>

#include "TileMapVisualiser.h"

class RandomWalkDungeonGenerator {
    int iterations = 50;
    sf::Vector2i startPosition;
    int walkLength = 50;
    bool startRandomlyEachIteration = true;
    std::unordered_set<sf::Vector2i> dungeon;
    std::unordered_set<sf::Vector2i> floorPositions;
    TileMapVisualiser visualiser;



public:
    RandomWalkDungeonGenerator(TileMap &tilemap,TileMap& wallTileMap, Floor &tile,Floor &wallTile);

    void runProceduralGeneration(TileMap &tilemap,TileMap& wallTileMap, Floor &tile,Floor &wallTile);

    std::unordered_set<sf::Vector2i> runRandomWalk();


};
