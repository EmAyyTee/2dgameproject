#pragma once
#include <memory>
#include "Character.h"
#include "Player.h"
#include "SFML/Graphics/RectangleShape.hpp"


class GreenSlime : public Character{

    sf::RectangleShape detectionHitBox;
    sf::RectangleShape attackHitbox;

public:
    enum class GreenSlimeAnimation{
        SlimeIdle = 0,
        SlimeWalk = 1,
        SlimeHurt = 2
    };
    enum class GreenSlimeDetection {
        PlayerNotDetected = 0,
        PlayerDetected = 1
    };


    GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target);

    void update(float deltaTime, Player &player);

    void moveTowardsPlayer(Player &player, float deltaTime);

    void chooseAnimation();

    void checkForThePlayer(Player &player);

    void checkForTheDamage(Player &player);

    void draw(sf::RenderTarget &renderTarget) override;

private:
    GreenSlimeAnimation green_slime_animation;
    GreenSlimeDetection green_slime_detection;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer;
};

