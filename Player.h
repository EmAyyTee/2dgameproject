#pragma once
#include "Character.h"

class Player : public Character{

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
