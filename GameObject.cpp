#include "GameObject.h"

#include "SFML/Graphics/RenderTarget.hpp"

GameObject::GameObject(const sf::Vector2f &position)
    : position(position){}

void GameObject::draw(sf::RenderTarget &renderTarget) {
    renderTarget.draw(hitBox);
    renderTarget.draw(sprite);
}
