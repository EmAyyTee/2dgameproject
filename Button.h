#pragma once
#include <memory>
#include <vector>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Button {
    sf::Sprite sprite;
    sf::Texture playButton;

public:
    Button();
    void buttonDraw(sf::RenderTarget& renderTarget);
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> buttonTexturesPtr;
};
