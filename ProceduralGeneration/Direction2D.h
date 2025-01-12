#pragma once
#include "Vector2iHash.h"
#include <vector>
#include <random>
#include "SFML/System/Vector2.hpp"

class Direction2D {
public:
    static sf::Vector2i getRandomCardinalDirection();
};

