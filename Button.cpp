#include "Button.h"

#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"

Button::Button(){
    sprite.setTextureRect(sf::IntRect(0,0,168,88));
    sprite.setPosition(sf::Vector2f(876,496));
    if (playButton.loadFromFile("MainMenuTextures/png/Buttons/Rect-Medium/PlayText/Default.png")){
        sprite.setTexture(playButton);
    } else {
        std::cout << "TextureLoader::TextureLoader: Failed to load texture from file\n";
    }
}

void Button::buttonDraw(sf::RenderTarget &renderTarget){
    renderTarget.draw(sprite);
}

