#include "DamageUpgrade.h"
#include "PiercingUpgrade.h"

#include <iostream>

#include "SFML/Window/Mouse.hpp"

DamageUpgrade::DamageUpgrade() {
    text.setString("Damage Upgrade");
}

void DamageUpgrade::update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount) {
    text.setPosition({player.getPosition().x-400, player.getPosition().y-100});
    checkIfMouseIsHovered(window);
    TextButton::getInput(game_state);
    if (player.playerDamageLevel >= 4) {
        text.setFillColor(sf::Color::Black);
        if (upgradesCount < player.playerLevel) {
            game_state= GameState::LevelUpScreen;
        }
    } else if (clicked && player.playerDamageLevel <=3) {
        player.playerDamageLevel++;
        player.currentDamage ++;
        std::cout << "Damage is : " << player.currentDamage << "\n";
        clicked=false;
        upgradeSelected=true;
        upgradesCount++;
    }
}

void DamageUpgrade::draw(sf::RenderWindow &window) {
    window.draw(text);
}

void DamageUpgrade::checkIfMouseIsHovered(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition = {mousePosition.x - 400, mousePosition.y - 100};
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = text.getGlobalBounds();
    buttonBounds.left -= 400;
    buttonBounds.top -= 100;

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
        text.setFillColor(sf::Color::White);
    } else {
        buttonState = ButtonState::NotHovered;
        text.setFillColor(sf::Color::Yellow);
    }
}