
#include "ContinueTheGameButton.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

ContinueTheGameButton::ContinueTheGameButton() {
    text.setString("Continue");
}

void ContinueTheGameButton::update(Player &player, sf::RenderWindow &window, GameState &game_state, GameState toChangeGamestate) {
    text.setPosition({player.getPosition().x - 40, player.getPosition().y-100});
    checkIfMouseIsHovered(window);
    getInput(game_state, toChangeGamestate);

    clicked=false;

}

void ContinueTheGameButton::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void ContinueTheGameButton::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x- 40, mousePosition.y-100};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left -= 40;
    buttonBounds.top -= 100;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Red);
    }
}void ContinueTheGameButton::getInput(GameState &game_state, GameState toChangeGameState) {
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime().asSeconds() > 0.4f) {
            game_state = toChangeGameState;
            clicked = true;
            clickClock.restart();
        }
    }
}

void ContinueTheGameButton::resetTheClickClock() {
    clickClock.restart();
}
