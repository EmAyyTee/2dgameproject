#pragma once
#include "../TextButton.h"

class DashUpgrade : TextButton{
public:
    DashUpgrade();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount);

    void draw(sf::RenderWindow &window);

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget);
};
