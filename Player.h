#pragma once
#include <memory>

#include "Character.h"
#include "TextureLoader.h"

class Player : public Character{

public:
    enum class PlayerState {
        PlayerIdle = 0,
        PlayerWalkingRight = 1,
        PlayerWalkingLeft = 2,
    };



    Player(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playerTexturesPointer, sf::RenderWindow* renderTarget);

    void update(float deltaTime) override;

    void playerGetInput();

private:
    PlayerState playerState;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playerTexturesPointer;
};
