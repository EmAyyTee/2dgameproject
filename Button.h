#pragma once
#include <memory>
#include <vector>

#include "Animator.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Button {
protected:
    sf::Sprite sprite;
    sf::Texture playButton;
    sf::RenderWindow* renderTarget = nullptr;
    sf::Vector2f position;

public:
    Button(const sf::Vector2f& position, sf::RenderWindow* target);
    void buttonDraw(sf::RenderTarget& renderTarget) const;
    void update();
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> buttonTexturesPtr;

    Animator animator;
};
