#pragma once
#include "GameObject.h"
#include "Player.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class TextButton : public GameObject{
protected:
    sf::Font font;
    sf::Text text;
    bool clicked = false;
public:

    enum class ButtonState {
        NotHovered = 0,
        Hovered = 1
    };
    TextButton();

    virtual void update(Player &player, sf::RenderWindow &window,GameState &game_state);
    virtual void draw(sf::RenderWindow& renderTarget);
    virtual void checkIfMouseIsHovered(sf::RenderWindow &renderTarget);
    virtual void getInput(GameState &game_state);

protected:
    ButtonState buttonState;
};
