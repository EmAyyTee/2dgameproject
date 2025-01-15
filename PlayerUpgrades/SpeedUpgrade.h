#pragma once
#include "../TextButton.h"

class SpeedUpgrade : TextButton{
public:
    SpeedUpgrade();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount);

    void draw(sf::RenderWindow &window);

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget);
};
