#pragma once
#include "character.h"

class Player : public character{

public:
    enum class PlayerState {
        PlayerIdle = 0,
        PlayerWalkingRight = 1,
        PlayerWalkingLeft = 2,
    };
    Player(const sf::Vector2f& position);
    void update(float deltaTime) override;
    void playerGetInput();
private:
    PlayerState playerState;

};
