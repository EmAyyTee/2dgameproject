#pragma once
#include "../TextButton.h"

class DamageUpgrade : TextButton{
public:
    DamageUpgrade();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &upgradeSelected, int &upgradesCount);

    void draw(sf::RenderWindow &window);

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget);
};
