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

    playerScoreText.setFont(font);
    playerScoreText.setCharacterSize(30);
    playerScoreText.setFillColor(sf::Color::Red);
    playerScoreText.setString("Player Score: " + std::to_string(playerScore));
    playerScoreText.setPosition(10,10);
}

void PlayerHud::update(Player &player) {
    playerHealthText.setString("Player Health: " + std::to_string(player.hitPoints));
    playerHealthText.setPosition(player.getPosition().x-900.0f,player.getPosition().y + 400.0f);
    playerScoreText.setString("Player Score: " + std::to_string(player.score));
    playerScoreText.setPosition(player.getPosition().x+700.0f,player.getPosition().y - 400.0f);
}

void PlayerHud::draw(sf::RenderWindow &window) {
    window.draw(playerHealthText);
    window.draw(playerScoreText);
}
