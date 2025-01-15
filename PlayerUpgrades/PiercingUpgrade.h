#pragma once
#include "../TextButton.h"

class PiercingUpgrade : TextButton{
public:
    PiercingUpgrade();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state) override;

    void draw(sf::RenderWindow &window);
};
