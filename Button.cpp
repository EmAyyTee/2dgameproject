#include "Button.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

Button::Button(const sf::Vector2f& position, sf::RenderWindow* target)
    : position(position), renderTarget(target) {
}

void Button::buttonDraw(sf::RenderTarget &renderTarget) const {
    renderTarget.draw(sprite);
}

void Button::update() {
    sprite.setPosition(position);
}



