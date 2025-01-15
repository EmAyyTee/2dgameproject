#include "WallGenerator.h"

#include <iostream>

#include "Direction2D.h"

WallGenerator::WallGenerator() {

}

std::unordered_set<sf::Vector2i> WallGenerator::createWalls(std::unordered_set<sf::Vector2i> floorPositions,
    TileMapVisualiser &tilemapVisualiser) {
    std::unordered_set<sf::Vector2i> basicWallPositions = findWallsInDirections(floorPositions, Direction2D::getCardinalDirections());
    for (auto& position : basicWallPositions) {
        tilemapVisualiser.paintSingleWall(position);
        // std::cout << "I'm trying to paint a wall tile at pos: " << position.x << " " << position.y << std::endl;
    }
    return basicWallPositions;
}

std::unordered_set<sf::Vector2i> WallGenerator::findWallsInDirections(std::unordered_set<sf::Vector2i> floorPositions, std::vector<sf::Vector2i> directionList) {
    std::unordered_set<sf::Vector2i> wallPositions;
    for (auto& position : floorPositions) {
        for (auto& direction : directionList) {
            // std::cout << "florr pos is: " << position.x << " "<< position.y << "\n";
            sf::Vector2i neighbourPos = position + direction;
            // std::cout << "Neighbouring pos is: " << neighbourPos.x << " "<< neighbourPos.y << "\n";
            if(!floorPositions.contains(neighbourPos)){
                wallPositions.emplace(neighbourPos);
                // std::cout << "placingNeighbour at pos: " << neighbourPos.x << " "<< neighbourPos.y << "\n";
            }
        }
    }
    return wallPositions;
}
