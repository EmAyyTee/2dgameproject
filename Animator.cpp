#include "Animator.h"

#include "TextureLoader.h"
#include "SFML/Graphics/Sprite.hpp"


Animator::Animator(int x, int y, int width, int height)
    : currentAnimationType(0){

    for (int i = 0; i < 13; i++) {
        frames[i] = {x + i * width, y, width, height };
    }
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
