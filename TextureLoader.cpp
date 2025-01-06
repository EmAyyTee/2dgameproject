#include "TextureLoader.h"

#include <iostream>
#include <ostream>

TextureLoader::TextureLoader() {

    //Loading Main Menu textures

    if (playButton.loadFromFile("MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Default.png")){
        mainMenuPlayButtonTextures.emplace_back(1,playButton);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Default.png\" texture from file\n";
    }
    if (playButtonHover.loadFromFile("MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Hover.png")){
        mainMenuPlayButtonTextures.emplace_back(1,playButtonHover);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Hover.png\" texture from file\n";
    }

    //Loading player textures

    if (playerIdleTexture.loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png")){
        playerTextures.emplace_back(6, playerIdleTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/IdleNoCelling.png\" texture from file\n";
    }
    
    if (playerWalkLeft.loadFromFile("PlayerCharacter/Archer/WalkRightNoCelling.png")){
        playerTextures.emplace_back(8, playerWalkLeft);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/WalkRightNoCelling.png\" texture from file\n";
    }
    
    if (playerWalkRight.loadFromFile("PlayerCharacter/Archer/WalkLeftNoCelling.png")){
        playerTextures.emplace_back(8, playerWalkRight);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/WalkLeftNoCelling.png\" texture from file\n";
    }

    allPlayerTextures.emplace("playerTextures", playerTextures);

    //Loading Player arrow textures

    if (arrowUpTexture.loadFromFile("PlayerCharacter/Archer/ArrowUp.png")){
        arrowTextures.emplace_back(1, arrowUpTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }
    if (arrowDownTexture.loadFromFile("PlayerCharacter/Archer/ArrowDown.png")){
        arrowTextures.emplace_back(1, arrowDownTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }
    if (arrowLeftTexture.loadFromFile("PlayerCharacter/Archer/ArrowLeft.png")){
        arrowTextures.emplace_back(1, arrowLeftTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }
    if (arrowRightTexture.loadFromFile("PlayerCharacter/Archer/ArrowRight.png")){
        arrowTextures.emplace_back(1, arrowRightTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"PlayerCharacter/Archer/ArrowUp.png\" texture from file\n";
    }

    allPlayerTextures.emplace("arrowTextures", arrowTextures);

    //Loading GreenSlime textures

    //Loading Ilde textures

    if (greenSlimeIdleTexture.loadFromFile("EnemiesTextures/GreenSlime/Idle/Slime1_Idle_full.png")){
        greenSlimeTextures.emplace_back(6, greenSlimeIdleTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Hurt/Slime1_Idle_full.png\" texture from file\n";
    }
    if (greenSlimeWalkingTexture.loadFromFile("EnemiesTextures/GreenSlime/Walk/Slime1_Walk_full.png")){

        //Adding all the animations of slime for all the states: Up, down, left and right which gives us 4 times.

        greenSlimeTextures.emplace_back(8, greenSlimeWalkingTexture);
        greenSlimeTextures.emplace_back(8, greenSlimeWalkingTexture);
        greenSlimeTextures.emplace_back(8, greenSlimeWalkingTexture);
        greenSlimeTextures.emplace_back(8, greenSlimeWalkingTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Walk/Slime1_Walk_full.png\" texture from file\n";
    }

    // Loading Hurt Textures

    if (greenSlimeHurtTexture.loadFromFile("EnemiesTextures/GreenSlime/Hurt/Slime1_Hurt_full.png")){
        greenSlimeTextures.emplace_back(5, greenSlimeHurtTexture);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load \"EnemiesTextures/GreenSlime/Hurt/Slime1_Hurt_full.png\" texture from file\n";
    }
}
