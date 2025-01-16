
#include "PlayButton.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

PlayButton::PlayButton() {
    text.setString("Play");
}

void PlayButton::update(Player &player, sf::RenderWindow &window, GameState &game_state, GameState toChangeGameState) {
    text.setPosition({player.getPosition().x, player.getPosition().y});
    checkIfMouseIsHovered(window);
    getInput(game_state, toChangeGameState);

    clicked=false;

}

void PlayButton::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void PlayButton::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x, mousePosition.y};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.top -= 0;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Red);
    }
}

void PlayButton::getInput(GameState &game_state, GameState toChangeGameState) {
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime().asSeconds() > 0.4f) {
            game_state = toChangeGameState;
            clicked = true;
            clickClock.restart();
        }
    }
}
