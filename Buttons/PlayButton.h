#pragma once
#include "../TextButton.h"

class PlayButton : TextButton{
public:
    PlayButton();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, GameState toChangeGameState);

    void draw(sf::RenderWindow &window);

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget);
    void getInput(GameState &game_state, GameState toChangeGameState);

};
