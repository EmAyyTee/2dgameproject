#include "PlayerHud.h"

#include <iostream>
#include <ostream>

PlayerHud::PlayerHud(int &playerHealth, int &playerScore) {
    if (!font.loadFromFile("Font/Blocky5x7.ttf")) {
        std::cerr << "Failed to load font." << "\n";
        return;
    }
    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(30);
    playerHealthText.setFillColor(sf::Color::Red);
    playerHealthText.setString("Player Health: " + std::to_string(playerHealth));
    playerHealthText.setPosition(10,10);
}

void PlayerHud::update(Player &player) {
    playerHealthText.setString("Player Health: " + std::to_string(player.hitPoints));
    playerHealthText.setPosition(player.getPosition().x-480.0f,player.getPosition().y - 270.0f);
}

void PlayerHud::draw(sf::RenderWindow &window) {

    window.draw(playerHealthText);
}
