#pragma once
#include <memory>

#include "Animator.h"
#include "GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"

class PlayerArrow : public GameObject{
protected:
    sf::RenderWindow * renderTarget;
    std::vector<std::pair <int, sf::Texture>> *arrowTextures;

public:
    enum class ArrowDirection {
        Up = 0,
        Down = 1,
        Left = 2,
        Right = 3
    };

    PlayerArrow(const sf::Vector2f& position,const sf::Vector2f &target, std::vector<std::pair <int, sf::Texture>> *playerTexturesPointer,
        sf::RenderWindow* renderTarget);

    void chooseAnimation(sf::Vector2f directionalVector);


    Animator animator;
private:
    ArrowDirection direction;
    sf::Vector2f target;
};

