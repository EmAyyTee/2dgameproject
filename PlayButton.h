#pragma once
#include <memory>
#include <vector>

#include "Button.h"
#include "GameState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

class PlayButton : public Button{
    public:
    enum class ButtonState {
        NotHovered = 0,
        Hovered = 1
    };
    PlayButton(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playerTexturesPointer,
    sf::RenderWindow* renderTarget);

    void update(float deltaTime,GameState &game_state);

    void checkIfMouseIsHovered();

    void getInput(GameState &game_state);

private:
    ButtonState buttonState;
    std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playButtonTexturesPointer;
};




