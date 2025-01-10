#include "TextureLoader.h"

#include <iostream>
#include <ostream>

TextureLoader::TextureLoader() {
    loadPlayerTextures();
    loadGreenSlimeTextures();
    loadMainMenuTextures();
}


void TextureLoader::loadPlayerTextures() {
    //Loading all player textures
    loadPlayerWalkingTextures();
    loadArrowTextures();
    loadPlayerShootTextures();
}
void TextureLoader::loadArrowTextures() {
    //loading all plyer arrow textures
    if (textureLoader.loadFromFile("PlayerCharacter/Archer/ArrowUp.png")){
        arrowTextures.emplace_back(1, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }
    if (textureLoader.loadFromFile("PlayerCharacter/Archer/ArrowDown.png")){
        arrowTextures.emplace_back(1, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }
    if (textureLoader.loadFromFile("PlayerCharacter/Archer/ArrowLeft.png")){
        arrowTextures.emplace_back(1, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }
    if (textureLoader.loadFromFile("PlayerCharacter/Archer/ArrowRight.png")){
        arrowTextures.emplace_back(1, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }

    allPlayerTextures.emplace("arrowTextures", arrowTextures);
}

void TextureLoader::loadPlayerWalkingTextures() {
    //Loading player walking textures

    if (textureLoader.loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png")){
        playerTextures.emplace_back(6, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/IdleNoCelling.png\" texture from file\n";
    }

    if (textureLoader.loadFromFile("PlayerCharacter/Archer/WalkRightNoCelling.png")){
        playerTextures.emplace_back(8, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/WalkRightNoCelling.png\" texture from file\n";
    }

    if (textureLoader.loadFromFile("PlayerCharacter/Archer/WalkLeftNoCelling.png")){
        playerTextures.emplace_back(8, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/WalkLeftNoCelling.png\" texture from file\n";
    }
    allPlayerTextures.emplace("playerTextures", playerTextures);
}

void TextureLoader::loadPlayerShootTextures() {
    //Loading all Player Shoot animations

    if (textureLoader.loadFromFile("PlayerCharacter/Archer/Shot_1.png")){
        playerShootTextures.emplace_back(14, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/Shot_1.png\" texture from file\n";
    }

    if (textureLoader.loadFromFile("PlayerCharacter/Archer/Shot1_R.png")){
        playerShootTextures.emplace_back(14, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/Shot_1R.png\" texture from file\n";
    }
    allPlayerTextures["playerTextures"].insert(
    allPlayerTextures["playerTextures"].end(),
    playerShootTextures.begin(),
    playerShootTextures.end()
);
}

void TextureLoader::loadGreenSlimeTextures() {
    //Loading GreenSlime textures

    //Loading Ilde textures

    if (textureLoader.loadFromFile("EnemiesTextures/GreenSlime/Idle/Slime1_Idle_full.png")){
        greenSlimeTextures.emplace_back(6, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Hurt/Slime1_Idle_full.png\" texture from file\n";
    }
    // Loading walking textures
    if (textureLoader.loadFromFile("EnemiesTextures/GreenSlime/Walk/Slime1_Walk_full.png")){
        greenSlimeTextures.emplace_back(8, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Walk/Slime1_Walk_full.png\" texture from file\n";
    }

    // Loading Hurt Textures

    if (textureLoader.loadFromFile("EnemiesTextures/GreenSlime/Hurt/Slime1_Hurt_full.png")){
        greenSlimeTextures.emplace_back(5, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Hurt/Slime1_Hurt_full.png\" texture from file\n";
    }

    // Loading attack textures

    if (textureLoader.loadFromFile("EnemiesTextures/GreenSlime/Attack/Slime1_Attack_full.png")){
        greenSlimeTextures.emplace_back(5, textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Attack/Slime1_Attack_full.png\" texture from file\n";
    }
}

void TextureLoader::loadMainMenuTextures() {
    //Loading Main Menu textures

    if (textureLoader.loadFromFile("MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Default.png")){
        mainMenuPlayButtonTextures.emplace_back(1,textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Default.png\" texture from file\n";
    }
    if (textureLoader.loadFromFile("MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Hover.png")){
        mainMenuPlayButtonTextures.emplace_back(1,textureLoader);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Hover.png\" texture from file\n";
    }
}
