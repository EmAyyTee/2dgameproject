#pragma once
#include <memory>
#include "Character.h"
#include "Player.h"
#include "SFML/Graphics/RectangleShape.hpp"


class GreenSlime : public Character{
protected:

    sf::RectangleShape detectionHitBox;
    sf::RectangleShape attackHitbox;
    bool isAttacking = false;
    bool isDealingDamage = true;
    sf::Vector2f attackTargetPosition;
    sf::FloatRect targetBounds;
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

    int slimeVariant = 0;


    GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target);

    GreenSlime() = default;

    ~GreenSlime() = default;

    virtual void update(float deltaTime, Player &player);

    virtual void normaliseVector(sf::Vector2f position);

    virtual void moveTowardsPlayer(Player &player, float deltaTime);

    virtual void chooseAnimation();

    virtual void checkForThePlayer(Player &player);

    virtual void checkForTheDamage(Player &player);

    virtual void attack(Player &player);

    void draw(sf::RenderTarget &renderTarget) override;

    virtual void saveToFile(std::ofstream &file) const;
    virtual void loadFromFile(std::ifstream &file);

    virtual sf::Vector2f getPosition();
    virtual void setPosition(sf::Vector2f position);

protected:
    GreenSlimeAnimation green_slime_animation;
    GreenSlimeDetection green_slime_detection;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer;
    BetterClock damageClock;
    sf::Clock atackCooldownClock;
    sf::Clock attentionClock;
    float cooldownForDealingDamage = 0.5f;
    float cooldownForBeingAbleToAttack = 2.0f;
    float slimeSpeedModifier;
};

