#pragma once
#include "Player.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class PlayerHud {
public:
    sf::Font font;
    sf::Text playerHealthText;
    sf::Text playerScoreText;

    PlayerHud(int &playerHealth, int &playerScore);

    void update(Player &player);

    void draw(sf::RenderWindow &window);
};
