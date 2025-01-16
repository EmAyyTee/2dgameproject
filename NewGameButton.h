#pragma once
#include "TextButton.h"

class NewGameButton : TextButton{
public:
    bool iClicked = false;

    NewGameButton(std::string label);

    bool update(Player &player, sf::RenderWindow &window, GameState &game_state);

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &isGameSaved, bool &shouldTheGameSave);

    void draw(sf::RenderWindow &window) override;

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget) override;

    void getInput(GameState &game_state);
};
