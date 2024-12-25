#pragma once
#include <map>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Animation {
    int nFrames = 6;
    static constexpr  float holdTime = 0.1f;

    int iFrame = 0, currentAnimationType;
    float time = 0.0f;

    // int is representing the number of sprites in the animation

    std::map<int, sf::Texture> textures;
    sf::IntRect frames[8];

    void Advance();

public:
    Animation(int x, int y, int width, int height);
    void applyToSprite( sf::Sprite& sprite);
    void Update(float deltaTime, int animationType);
};
