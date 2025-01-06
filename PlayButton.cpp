#include "PlayButton.h"

#include "Button.h"
#include "SFML/Window/Mouse.hpp"

PlayButton::PlayButton(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> playButtonTexturesPointer,
                       sf::RenderWindow* renderTarget)
        : Button(position, renderTarget), playButtonTexturesPointer(std::move(playButtonTexturesPointer)){
    animator.calculateTheFrames(0, 0, 168, 88);
    animator.setNumberOfFrames(1);
    buttonState = ButtonState::NotHovered;
}

void PlayButton::update(float deltaTime,GameState &game_state) {
    Button::update();
    checkIfMouseIsHovered();
    getInput(game_state);

    animator.Update(deltaTime, static_cast<int>(buttonState), sprite, playButtonTexturesPointer.get());
}
void PlayButton::checkIfMouseIsHovered() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*renderTarget);
    sf::Vector2f worldPosition = renderTarget->mapPixelToCoords(mousePosition);
    sf::FloatRect buttonBounds = sprite.getGlobalBounds();

    if (buttonBounds.contains(worldPosition)) {
        buttonState = ButtonState::Hovered;
    } else {
        buttonState = ButtonState::NotHovered;
    }
}

void PlayButton::getInput(GameState &game_state) {
    if (buttonState == ButtonState::Hovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            game_state = GameState::Running;
        }
    }
}

