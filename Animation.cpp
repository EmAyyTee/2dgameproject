#include "Animation.h"

#include "character.h"
#include "TextureLoader.h"
#include "SFML/Graphics/Sprite.hpp"

TextureLoader textureLoader;

Animation::Animation(int x, int y, int width, int height)
    : currentAnimationType(0){

    for (int i = 0; i < 8; i++) {
        frames[i] = {x + i * width, y, width, height };
    }
}
void Animation::applyToSprite( sf::Sprite& sprite) {
    sprite.setTexture(textureLoader.textures[currentAnimationType]);
    sprite.setTextureRect(frames[iFrame]);
}
void Animation::Update(float deltaTime, int animationType) {
    if (currentAnimationType != animationType) {
        currentAnimationType = animationType;
        iFrame = 0;
        time = 0.0f;
        if (currentAnimationType == 0) {
            nFrames = 6;
        }
        else {
            nFrames = 8;
        }
    }
    time += deltaTime;
    while (time >= holdTime) {
        time -= holdTime;
        Advance();
    }
}
void Animation::Advance() {
    if(++iFrame >= nFrames) {
        iFrame = 0;
    }
}
