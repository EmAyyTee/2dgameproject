#pragma once
#include <memory>
#include "Character.h"


class GreenSlime : public Character{

public:
    enum class GreenSlimeState{
        SlimeIdle = 0
    };


    GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer);

    void update(float deltaTime) override;

private:
    GreenSlimeState green_slime_state;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer;
};

