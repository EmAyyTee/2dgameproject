#pragma once
#include <memory>

#include "Animator.h"
#include "Character.h"
#include "GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"

class PlayerArrow : public GameObject{
protected:
    sf::RenderWindow * renderTarget;
    std::vector<std::pair <int, sf::Texture>> *arrowTextures;
    sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f directionalVector;
    float magnitude;

public:
    enum class ArrowDirection {
        Up = 0,
        Down = 1,
        Left = 2,
        Right = 3
    };

    PlayerArrow(sf::Vector2f position, sf::Vector2f target, std::vector<std::pair <int, sf::Texture>> *playerTexturesPointer,
        sf::RenderWindow* renderTarget);

    void chooseAnimation();

    void update(float deltaTime) override;

    bool checkArrowLifeTime();

    sf::RectangleShape& getArrowHitBox();

    Animator animator;
private:
    float maxLifetime = 5.0f;
    ArrowDirection directionAnimation;
    sf::Vector2f target;
    sf::Vector2f hitBoxPosition;
    sf::Clock arrowClock;
};

