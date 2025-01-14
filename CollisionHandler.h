#pragma once
#include "GreenSlime.h"
#include "SFML/Graphics/Rect.hpp"

class CollisionHandler {
public:

    CollisionHandler() = default;

    bool checkCollision(sf::FloatRect &rectA, sf::FloatRect &rectB);

    void checkGreenSlimesCollisions(std::vector<GreenSlime> &greenSlimes);

    void handleGreenSlimeCollision(GreenSlime &slime1, GreenSlime &slime2);
};
