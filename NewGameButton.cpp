
#include "NewGameButton.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

NewGameButton::NewGameButton(std::string label) {
    text.setString(label);
}

bool NewGameButton::update(Player &player, sf::RenderWindow &window, GameState &game_state) {
    text.setPosition({player.getPosition().x-50, player.getPosition().y});
    checkIfMouseIsHovered(window);
    getInput(game_state);
    return iClicked;
}

void NewGameButton::update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &isGameSaved, bool &shouldTheGameSave) {
    text.setPosition({player.getPosition().x-50, player.getPosition().y-200});
    checkIfMouseIsHovered(window);
    TextButton::getInput(game_state);
}

void NewGameButton::getInput(GameState &game_state) {
    iClicked = false;
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime().asSeconds() > 0.4f) {
            iClicked = true;
            game_state = GameState::Running;
            clickClock.restart();
        }
    }
}


void NewGameButton::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void NewGameButton::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x - 50, mousePosition.y - 100};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left -= 50;
    buttonBounds.top -= 100;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Red);
    }
}