#include "ProceduralGenerationAlgorithms.h"

#include "Direction2D.h"

std::unordered_set<sf::Vector2i> ProceduralGenerationAlgorithms::path;

std::unordered_set<sf::Vector2i> ProceduralGenerationAlgorithms::simpleRandomWalk(
    sf::Vector2i startPosition, int walkLength) {

    sf::Vector2i previousPos = startPosition;

    path.emplace(startPosition);

    for (int i = 0; i < walkLength; i++) {
        sf::Vector2i newPos = previousPos + Direction2D::getRandomCardinalDirection();
        path.emplace(newPos);
        previousPos = newPos;
    }
    return path;
}
