#pragma once
class Animation {
    static constexpr int nFrames = 8;
    sttic constexpr  float holdTime = 0.1f;
    sf::Texture texture;
    sf::IntRect frames[nFrames];
    int Iframe = 0;
public:
    Animation(int x, int y, int width, int height);
};
