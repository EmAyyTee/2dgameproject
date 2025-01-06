#pragma once
#include <memory>
#include <vector>

#include "Animator.h"
#include "GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

class Button {
protected:
    sf::Texture playButton;
    sf::RenderWindow* renderTarget = nullptr;
    sf::Vector2f position;
    sf::Sprite sprite;
public:
    Button(const sf::Vector2f& position, sf::RenderWindow* target);
    void buttonDraw(sf::RenderTarget& renderTarget) const;
    void update();
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> buttonTexturesPtr;

    Animator animator;
};
