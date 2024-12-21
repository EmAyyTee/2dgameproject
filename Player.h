#pragma once
#include "Animation.h"
#include "character.h"

class Player : public character{
    Animation walkRight;
public:
    Player(const sf::Vector2f& position);
};
