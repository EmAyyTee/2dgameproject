#pragma once
#include "Vector2iHash.h"
#include <unordered_set>


#include "SFML/System/Vector2.hpp"

class ProceduralGenerationAlgorithms {

    ProceduralGenerationAlgorithms() = default;

public:
    static sf::Vector2i previousPos;
    static std::unordered_set<sf::Vector2i> path;
    static std::unordered_set<sf::Vector2i> simpleRandomWalk(sf::Vector2i startPosition, int walkLenght);
};
