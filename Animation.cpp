#include "Animation.h"

#include "character.h"
#include "SFML/Graphics/Sprite.hpp"

Animation::Animation(int x, int y, int width, int height)
    : currentAnimation(0){
    textures[0].loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png");
    textures[1].loadFromFile("PlayerCharacter/Archer/WalkRightNoCelling.png");
    textures[2].loadFromFile("PlayerCharacter/Archer/WalkRightNoCelling.png");

    for (int i = 0; i < nFrames; i++) {
        frames[i] = {x + i * width, y, width, height };
    }
}
void Animation::applyToSpite( sf::Sprite& sprite) {
    sprite.setTexture(textures[currentAnimation]);
    sprite.setTextureRect(frames[iFrame]);
}
void Animation::Update(float deltaTime, int animationType) {
    if (currentAnimation != animationType) {
        currentAnimation = animationType;
        iFrame = 0;
        time = 0.0f;
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
