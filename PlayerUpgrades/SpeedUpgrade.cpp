#include "SpeedUpgrade.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

SpeedUpgrade::SpeedUpgrade() {
    text.setString("Speed Upgrade");
}

void SpeedUpgrade::update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount) {
    text.setPosition({player.getPosition().x+180, player.getPosition().y-100});
    checkIfMouseIsHovered(window);
    TextButton::getInput(game_state);
    if (player.playerSpeedLevel >= 2) {
        text.setFillColor(sf::Color::Black);
        if (upgradesCount < player.playerLevel) {
            game_state= GameState::LevelUpScreen;
        }
    } else if (clicked && player.playerSpeedLevel <=1) {
        player.playerSpeedLevel++;
        player.speedModifier = 1.2f;
        std::cout << "Speed is : " << player.speedModifier << "\n";
        clicked=false;
        upgradeSelected=true;
        upgradesCount++;
    }
}

void SpeedUpgrade::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void SpeedUpgrade::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x + 180, mousePosition.y - 100};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left += 180;
    buttonBounds.top -= 100;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Yellow);
    }
}