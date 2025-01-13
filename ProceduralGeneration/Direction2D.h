#pragma once
#include "Vector2iHash.h"
#include <vector>
#include <random>
#include <unordered_set>

#include "SFML/System/Vector2.hpp"

class Direction2D {
public:
    static sf::Vector2i getRandomCardinalDirection();

    static std::vector<sf::Vector2i> getCardinalDirectionsList();

    static std::vector<sf::Vector2i> cardinalDirections;
};

