#pragma once
#include <memory>
#include "Character.h"
#include "Player.h"
#include "SFML/Graphics/RectangleShape.hpp"


class GreenSlime : public Character{

    sf::Vector2f playerPosition;
    sf::Rect<float> slimeHitBox = sprite.getGlobalBounds();
    sf::RectangleShape hitBox;

public:
    enum class GreenSlimeState{
        SlimeIdle = 0,
        SlimeWalkRight = 1,
        SlimeWalkLeft = 2,
        SlimeWalkDown = 3,
        SlimeWalkUp = 4
    };


    GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target);

    void update(float deltaTime, Player &player);

    void moveTowardsPlayer(Player &player);

    void updateHitbox();

    void draw(sf::RenderTarget& renderTarget);

private:
    GreenSlimeState green_slime_state;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer;
};

