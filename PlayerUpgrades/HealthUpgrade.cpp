#include "HealthUpgrade.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

HealthUpgrade::HealthUpgrade() {
    text.setString("Health Upgrade");
}

void HealthUpgrade::update(Player &player, sf::RenderWindow &window, GameState &game_state,bool &upgradeSelected, int &upgradesCount) {
    text.setPosition({player.getPosition().x-120, player.getPosition().y-150});
    checkIfMouseIsHovered(window);
    TextButton::getInput(game_state);
    if (player.playerHealthLevel >= 1000) {
        text.setFillColor(sf::Color::Black);
        if (upgradesCount < player.playerLevel) {
            game_state= GameState::LevelUpScreen;
        }
    } else if (clicked && player.playerPiercingLevel <=1000) {
        player.playerHealthLevel++;
        player.hitPoints ++;
        std::cout << "Health is : " << player.playerHealthLevel << "\n";
        clicked=false;
        upgradeSelected = true;
        upgradesCount++;
    }
}

void HealthUpgrade::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void HealthUpgrade::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x - 120, mousePosition.y - 150};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left -= 120;
    buttonBounds.top -= 150;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Yellow);
    }
}