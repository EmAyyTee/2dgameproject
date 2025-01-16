#include "TextButton.h"

#include <iostream>
#include <ostream>

#include "SFML/Window/Mouse.hpp"

TextButton::TextButton() {
    if(!font.loadFromFile("Font/Blocky5x7.ttf")) {
        std::cerr << "Error loading font" << "\n";
    }
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Yellow);
}

void TextButton::update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount) {
    text.setPosition({player.getPosition().x, player.getPosition().y});
    upgradeSelected = false;
    checkIfMouseIsHovered(window);
    getInput(game_state);
}

void TextButton::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void TextButton::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Yellow);
    }
}

void TextButton::getInput(GameState &game_state) {
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime().asSeconds() > 0.4f) {
            game_state = GameState::Running;
            clicked = true;
            clickClock.restart();
        }
    }
}