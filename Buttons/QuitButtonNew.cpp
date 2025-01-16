
#include "QuitButtonNew.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

QuitButtonNew::QuitButtonNew() {
    text.setString("Quit");
}

void QuitButtonNew::update(Player &player, sf::RenderWindow &window, GameState &game_state, GameState toChangeGamestate) {
    text.setPosition({player.getPosition().x, player.getPosition().y+100});
    checkIfMouseIsHovered(window);
    getInput(game_state, toChangeGamestate);


}

void QuitButtonNew::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void QuitButtonNew::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x, mousePosition.y+100};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.top += 100;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Red);
    }
}

void QuitButtonNew::getInput(GameState &game_state, GameState toChangeGameState) {
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime().asSeconds() > 0.4f) {
            game_state = toChangeGameState;
            iClicked = true;
            clickClock.restart();
        }
    }
}