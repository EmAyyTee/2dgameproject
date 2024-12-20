#pragma once
#include "character.h"

class Player : public character{
public:

    Player();
    void idleAnimation(int row, float deltaTime);
};
