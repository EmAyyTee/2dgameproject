#pragma once
#include "TextButton.h"

class NewGameButton : TextButton{
public:
    bool iClicked = false;

    NewGameButton();

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, GameState toChangeGamestate);

    void draw(sf::RenderWindow &window) override;

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget) override;

    void getInput(GameState &game_state, GameState toChangeGamestate);

    void setIClicked(bool clicked);

    void resetTheClickClock();
};
