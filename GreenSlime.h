#pragma once
#include <memory>
#include "Character.h"
#include "Player.h"
#include "SFML/Graphics/RectangleShape.hpp"


class GreenSlime : public Character{

    sf::RectangleShape detectionHitBox;
    sf::RectangleShape attackHitbox;
    bool isAttacking = false;
    bool isDealingDamage = true;
    sf::Vector2f attackTargetPosition;
    int greenSlimeDamage = 1;

public:
    enum class GreenSlimeAnimation{
        SlimeIdle = 0,
        SlimeWalk = 1,
        SlimeHurt = 2,
        SlimeAttacking = 3
    };
    enum class GreenSlimeDetection {
        PlayerNotDetected = 0,
        PlayerDetected = 1
    };


    GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target);

    void update(float deltaTime, Player &player);

    void normaliseVector(sf::Vector2f position);

    void moveTowardsPlayer(Player &player, float deltaTime);

    void chooseAnimation();

    void checkForThePlayer(Player &player);

    void checkForTheDamage(Player &player);

    void attack(Player &player);

    void draw(sf::RenderTarget &renderTarget) override;

private:
    GreenSlimeAnimation green_slime_animation;
    GreenSlimeDetection green_slime_detection;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer;
    BetterClock damageClock;
    float cooldownForDealingDamage = 0.5f;
};

