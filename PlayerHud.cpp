#include "PlayerHud.h"

#include <iostream>
#include <ostream>
#include <fmt/format.h>

PlayerHud::PlayerHud(Player &player) {
    if (!font.loadFromFile("Font/Blocky5x7.ttf")) {
        std::cerr << "Failed to load font." << "\n";
        return;
    }
    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(30);
    playerHealthText.setFillColor(sf::Color::Blue);
    playerHealthText.setPosition(10,10);

    playerScoreText.setFont(font);
    playerScoreText.setCharacterSize(30);
    playerScoreText.setFillColor(sf::Color::White);
    playerScoreText.setPosition(10,10);

    playerLevelText.setFont(font);
    playerLevelText.setCharacterSize(30);
    playerLevelText.setFillColor(sf::Color::Magenta);
    playerLevelText.setPosition(10,10);

    shotCooldown.setFont(font);
    shotCooldown.setCharacterSize(30);
    shotCooldown.setFillColor(sf::Color::Blue);
    shotCooldown.setPosition(10,10);

    dashCooldown.setFont(font);
    dashCooldown.setCharacterSize(30);
    dashCooldown.setFillColor(sf::Color::Blue);
    dashCooldown.setPosition(10,10);
}

void PlayerHud::update(Player &player) {
    playerHealthText.setString("Player Health: " + std::to_string(player.hitPoints));
    playerHealthText.setPosition(player.getPosition().x-900.0f,player.getPosition().y + 400.0f);

    playerScoreText.setString("Player Score: " + std::to_string(player.score));
    playerScoreText.setPosition(player.getPosition().x+700.0f,player.getPosition().y - 500.0f);

    playerLevelText.setString("Level: " + std::to_string(player.playerLevel));
    playerLevelText.setPosition(player.getPosition().x,player.getPosition().y - 500.0f);

    float timeToShoot = 0.5f - player.shotClock.getElapsedTime().asSeconds();

    float timeToDash = 5.0f - player.dashClock.getElapsedTime().asSeconds();

    if (timeToShoot > 0 ) {
        shotCooldown.setString(fmt::format("Next Arrow: {:.2f}", timeToShoot));
    } else {
        shotCooldown.setString("Arrow Ready!");
    }
    shotCooldown.setPosition(player.getPosition().x - 630,player.getPosition().y + 400.0f);

    if (player.playerDashAbility >=2){
        if (timeToDash > 0) {
            dashCooldown.setString(fmt::format("Next Dash In: {:.2f}", timeToDash));
        } else {
            dashCooldown.setString("Dash Ready!");
        }
        dashCooldown.setPosition(player.getPosition().x - 380,player.getPosition().y + 400.0f);
    } else {
        dashCooldown.setString("");
    }

}

void PlayerHud::draw(sf::RenderWindow &window) {
    window.draw(playerHealthText);
    window.draw(playerScoreText);
    window.draw(playerLevelText);
    window.draw(shotCooldown);
    window.draw(dashCooldown);
}
