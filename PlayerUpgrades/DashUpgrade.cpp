#include "DashUpgrade.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

DashUpgrade::DashUpgrade() {
    text.setString("Dash Ability");
}

void DashUpgrade::update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount) {
    text.setPosition({player.getPosition().x+180, player.getPosition().y-150});
    checkIfMouseIsHovered(window);
    TextButton::getInput(game_state);
    if (player.playerDashAbility >= 2) {
        text.setFillColor(sf::Color::Black);
        if (upgradesCount < player.playerLevel) {
            game_state= GameState::LevelUpScreen;
        }
    } else if (clicked && player.playerDashAbility <=1) {
        player.playerDashAbility++;
        std::cout << "Dash is on\n";
        clicked=false;
        upgradeSelected=true;
        upgradesCount++;
    }
}

void DashUpgrade::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void DashUpgrade::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x + 180, mousePosition.y - 150};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left += 180;
    buttonBounds.top -= 150;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Yellow);
    }
}