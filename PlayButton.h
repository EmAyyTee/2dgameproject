#pragma once
#include <memory>
#include <vector>

#include "Button.h"
#include "GameState.h"
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

class PlayButton : public Button{
    public:
    enum class ButtonState {
        NotHovered = 0,
        Hovered = 1
    };

    ButtonState buttonState;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playButtonTexturesPointer;
    sf::Clock clickClock;
    bool iGotInput = false;


    PlayButton(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playerTexturesPointer,
    sf::RenderWindow* renderTarget);


    virtual void update(float deltaTime,GameState &game_state, GameState toChangeGameState);

    virtual void update(float deltaTime,GameState &game_state,Player &player, GameState toChangeGameState);


    virtual void update(float deltaTime,GameState &game_state, Player &player, GameState toChangeGameState, bool &shouldTheGameSave);

    virtual void update(float deltaTime,GameState &game_state, Player &player, GameState toChangeGameState,bool &shouldTheGameSave, bool isThatTheQuitButton);

    virtual void update(float deltaTime,GameState &game_state, Player &player, GameState toChangeGameState,bool &shouldTheGameSave, bool isThatTheQuitButton, bool isThatDuringTheGame);



    virtual void checkIfMouseIsHovered();

    virtual void getInput(GameState &game_state, GameState toChangeGameState);

    virtual void setTheFrames(int x, int y, int width, int height);


};




