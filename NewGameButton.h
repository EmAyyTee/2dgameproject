#pragma once
#include "TextButton.h"

class NewGameButton : TextButton{
public:
    NewGameButton(std::string label);

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &newGameChosen);

    void update(Player &player, sf::RenderWindow &window, GameState &game_state, bool &isGameSaved, bool &shouldTheGameSave);

    void draw(sf::RenderWindow &window) override;

    void checkIfMouseIsHovered(sf::RenderWindow &renderTarget) override;

    void getInput(GameState &game_state);
};
