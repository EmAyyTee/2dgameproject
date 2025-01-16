#pragma once
#include "../TextButton.h"

class QuitButtonNew : TextButton{
public:

    bool iClicked = false;
    QuitButtonNew();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, GameState toChangeGamestate);

    void draw(sf::RenderWindow &window);

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget);

    void getInput(GameState &game_state, GameState toChangeGameState);

};
