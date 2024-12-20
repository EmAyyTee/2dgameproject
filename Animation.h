#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"

class Animation {
    static constexpr int nFrames = 8;
    static constexpr  float holdTime = 0.1f;
    sf::Texture texture;
    sf::IntRect frames[nFrames];
    int Iframe = 0;
public:
    Animation(int x, int y, int width, int height);
};
