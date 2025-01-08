#include "Animator.h"

#include "TextureLoader.h"
#include "SFML/Graphics/Sprite.hpp"


Animator::Animator()
    : currentAnimationType(0), nFrames(nFrames){
}

void Animator::applyToSprite(sf::Sprite& sprite, std::vector<std::pair <int, sf::Texture>> *textures) {
    sprite.setTexture(textures -> at(currentAnimationType).second);
    sprite.setTextureRect(frames[iFrame]);
}

void Animator::Update(float deltaTime, int animationType, sf::Sprite& sprite, std::vector<std::pair <int, sf::Texture>> *textures) {

    applyToSprite( sprite,textures);

    if (currentAnimationType != animationType) {
        currentAnimationType = animationType;
        iFrame = 0;
        time = 0.0f;
        nFrames = textures -> at(currentAnimationType).first;
    }
    time += deltaTime;
    while (time >= holdTime) {
        time -= holdTime;
        Advance();
    }

}

void Animator::Advance() {
    if(++iFrame >= nFrames) {
        iFrame = 0;
    }
}

void Animator::calculateTheFrames(int x, int y, int width, int height) {
    for (int i = 0; i < 14; i++) {
        frames[i] = {x + i * width, y * height, width, height };
    }
}

void Animator::setNumberOfFrames(int nFrames) {
    this -> nFrames = nFrames;
}
