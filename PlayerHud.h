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
    sf::Text playerLevelText;
    sf::Text shotCooldown;
    sf::Text dashCooldown;


    PlayerHud(Player &player);

    void update(Player &player);

    void draw(sf::RenderWindow &window);
};
