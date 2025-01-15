#include "PiercingUpgrade.h"

#include <iostream>

PiercingUpgrade::PiercingUpgrade() {
    text.setString("Piercing Upgrade");
}

void PiercingUpgrade::update(Player &player, sf::RenderWindow &window, GameState &game_state) {
    TextButton::update(player, window, game_state);
    text.setPosition({player.getPosition().x, player.getPosition().y});
    if (clicked && player.playerPiercingLevel <=2) {
        player.playerPiercingLevel++;
        player.arrowsHp = player.arrowsHp * player.playerPiercingLevel;
        std::cout << "I upgrade the piercing!\n";
    } else if (player.playerPiercingLevel > 2) {
        text.setFillColor(sf::Color::Black);
    }
}

void PiercingUpgrade::draw(sf::RenderWindow &window) {
    window.draw(text);
}
