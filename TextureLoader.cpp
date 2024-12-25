#include "TextureLoader.h"

#include <iostream>
#include <ostream>

TextureLoader::TextureLoader() {
    
    
    if (playerIdleTexture.loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png")){
        textures.emplace_back(playerIdleTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
    
    if (playerWalkLeft.loadFromFile("PlayerCharacter/Archer/WalkRightNoCelling.png")){
        textures.emplace_back(playerWalkLeft);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
    
    if (playerWalkRight.loadFromFile("PlayerCharacter/Archer/WalkLeftNoCelling.png")){
        textures.emplace_back(playerWalkRight);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
    
}
