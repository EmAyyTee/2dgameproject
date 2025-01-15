#include "PiercingUpgrade.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

PiercingUpgrade::PiercingUpgrade() {
    text.setString("Piercing Upgrade");
}

void PiercingUpgrade::update(Player &player, sf::RenderWindow &window, GameState &game_state,bool &upgradeSelected, int &upgradesCount) {
    text.setPosition({player.getPosition().x-120, player.getPosition().y-100});
    checkIfMouseIsHovered(window);
    TextButton::getInput(game_state);
    if (player.playerPiercingLevel >= 3) {
        text.setFillColor(sf::Color::Black);
        if (upgradesCount < player.playerLevel) {
            game_state= GameState::LevelUpScreen;
        }
    } else if (clicked && player.playerPiercingLevel <=2) {
        player.playerPiercingLevel++;
        player.arrowsHp = player.arrowsHp + player.playerPiercingLevel;
        std::cout << "Piercing is : " << player.playerPiercingLevel << "\n";
        clicked=false;
        upgradeSelected = true;
        upgradesCount++;
    }
}

void PiercingUpgrade::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void PiercingUpgrade::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x - 120, mousePosition.y - 100};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left -= 120;
    buttonBounds.top -= 100;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Yellow);
    }
}