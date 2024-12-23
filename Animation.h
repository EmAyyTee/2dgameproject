#pragma once
#include <map>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Animation {
    int nFrames = 8;
    static constexpr  float holdTime = 0.1f;

    int iFrame = 0, currentAnimation;
    float time = 0.0f;
    std::map<int, sf::Texture> textures;
    sf::IntRect frames[8];

    void Advance();

public:
    Animation(int x, int y, int width, int height);
    void applyToSpite( sf::Sprite& sprite);
    void Update(float deltaTime, int animationType);
};
