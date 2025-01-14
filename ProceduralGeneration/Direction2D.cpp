#include "Direction2D.h"

#include <iostream>

#include "Vector2iHash.h"

sf::Vector2i Direction2D::getRandomCardinalDirection() {
    static std::vector<sf::Vector2i> cardinalDirections = {
        {0, 1},   // Up
        {1, 0},   // Right
        {0, -1},  // Down
        {-1, 0}   // Left
    };

    static std::mt19937 rng(std::random_device{}()); // Random number generator
    std::uniform_int_distribution<int> dist(0, cardinalDirections.size() - 1);

    return cardinalDirections[dist(rng)];
}