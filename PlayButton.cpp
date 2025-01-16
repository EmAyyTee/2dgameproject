#include "PlayButton.h"

#include <iostream>

#include "Button.h"
#include "SFML/Window/Mouse.hpp"

PlayButton::PlayButton(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playButtonTexturesPointer,
                       sf::RenderWindow* renderTarget)
        : Button(position, renderTarget), playButtonTexturesPointer(std::move(playButtonTexturesPointer)){
    animator.calculateTheFrames(0, 0, 168, 88);
    animator.setNumberOfFrames(1);
    buttonState = ButtonState::NotHovered;
}

void PlayButton::update(float deltaTime,GameState &game_state, GameState toChangeGameState) {
    Button::update();
    checkIfMouseIsHovered();
    getInput(game_state, toChangeGameState);
    iGotInput = false;

    animator.Update(deltaTime, static_cast<int>(buttonState), sprite, playButtonTexturesPointer.get());
}

void PlayButton::update(float deltaTime, GameState &game_state, Player &player, GameState toChangeGameState) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    position.x = player.getPosition().x - bounds.width /3;
    position.y = player.getPosition().y - bounds.height/3;
    update(deltaTime, game_state, toChangeGameState);
    iGotInput = false;

    animator.Update(deltaTime, static_cast<int>(buttonState), sprite, playButtonTexturesPointer.get());
}


void PlayButton::update(float deltaTime, GameState &game_state, Player &player, GameState toChangeGameState, bool& shouldTheGameSave) {

    sf::FloatRect bounds = sprite.getGlobalBounds();
    position.x = player.getPosition().x - bounds.width /3;
    position.y = player.getPosition().y - bounds.height/3;
    update(deltaTime, game_state, toChangeGameState);
    shouldTheGameSave = iGotInput;
    iGotInput = false;

}

void PlayButton::update(float deltaTime, GameState &game_state, Player &player, GameState toChangeGameState, bool& shouldTheGameSave, bool isThatTheQuitButton) {
    if(!isThatTheQuitButton) {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        position.x = player.getPosition().x - bounds.width /3;
        position.y = player.getPosition().y - bounds.height/3;
        update(deltaTime, game_state, toChangeGameState);
    }
    else {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        position.x = player.getPosition().x - bounds.width /3 + 20;
        position.y = player.getPosition().y - bounds.height/3 + 133;
        update(deltaTime, game_state, toChangeGameState);
    }
    shouldTheGameSave = true;
    iGotInput = false;
}

void PlayButton::update(float deltaTime, GameState &game_state, Player &player, GameState toChangeGameState, bool &shouldTheGameSave, bool isThatTheQuitButton, bool isThatDuringTheGame) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    position.x = player.getPosition().x - bounds.width /3 + 20;
    position.y = player.getPosition().y - bounds.height/3 + 133;
    update(deltaTime, game_state, toChangeGameState);
    shouldTheGameSave = iGotInput;
    iGotInput = false;
}


void PlayButton::checkIfMouseIsHovered() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*renderTarget);
    sf::Vector2f worldPosition = renderTarget->mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = sprite.getGlobalBounds();

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
    } else {
        buttonState = ButtonState::NotHovered;
    }
}

void PlayButton::getInput(GameState &game_state, GameState toChangeGameState) {
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime().asSeconds() > 0.4f) {
            game_state = toChangeGameState;
            std::cout << "I change the game state to: " << static_cast<int>(toChangeGameState) << "\n";
            iGotInput = true;
        }
    }
}

void PlayButton::setTheFrames(int x, int y, int width, int height) {
    animator.calculateTheFrames(x,y,width,height);
}

