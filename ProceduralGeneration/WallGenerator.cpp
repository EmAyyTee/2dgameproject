#include "WallGenerator.h"

#include "Direction2D.h"

//You might want to change getRandomCardinal to getCardinalList later if sum don't work

void WallGenerator::createWalls(std::unordered_set<sf::Vector2i> floorPositions, TileMapVisualiser tileMapVisualiser) {
    basicWallPositions = {findWallsInDirections(floorPositions, Direction2D::getRandomCardinalDirection())};
}
sf::Vector2i WallGenerator::findWallsInDirections(std::unordered_set<sf::Vector2i> floorPositions, sf::Vector2i directionsList) {
    for (sf::Vector2i position : floorPositions) {
        for (sf::Vector2i direction : directionsList) {
            sf::Vector2i neighbourPos = position + direction;
            if(!floorPositions.contains(neighbourPos)) {
                wallPositions.emplace(neighbourPos);
            }
        }
    }
}
