#include "ProceduralGenerationAlgorithms.h"

#include <iostream>
#include <ostream>

#include "Direction2D.h"

std::unordered_set<sf::Vector2i> ProceduralGenerationAlgorithms::path;
sf::Vector2i ProceduralGenerationAlgorithms::previousPos = {0,0};


std::unordered_set<sf::Vector2i> ProceduralGenerationAlgorithms::simpleRandomWalk(
    sf::Vector2i startPosition, int walkLength) {


    previousPos = startPosition;
    path.emplace(startPosition);
//Use for debug if something goes wrong with the gen

    // std::cout << "StartPosx in PGA: " << startPosition.x<< " ";
    // std::cout << "StartPosy in PGA: " << startPosition.y << std::endl;


    // std::cout << "previous pos in PGA: " << previousPos.x << ", " << previousPos.y << std::endl;

    for (int i = 0; i < walkLength; i++) {
        sf::Vector2i newPos = previousPos + Direction2D::getRandomCardinalDirection();
        path.emplace(newPos);
        previousPos = newPos;
        // std::cout << previousPos.x << ", " << previousPos.y << std::endl;
    }
    return path;
}
