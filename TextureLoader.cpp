#include "TextureLoader.h"

#include <iostream>
#include <ostream>

TextureLoader::TextureLoader() {
    
    
    if (playerIdleTexture.loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png")){
        playerTextures.emplace_back(6, playerIdleTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
    
    if (playerWalkLeft.loadFromFile("PlayerCharacter/Archer/WalkRightNoCelling.png")){
        playerTextures.emplace_back(8, playerWalkLeft);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
    
    if (playerWalkRight.loadFromFile("PlayerCharacter/Archer/WalkLeftNoCelling.png")){
        playerTextures.emplace_back(8, playerWalkRight);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
    
}
