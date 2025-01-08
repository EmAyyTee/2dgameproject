#include "Tile.h"

Tile::Tile(float x, float y,float gridSizeF) {
    shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
}

void Tile::update() {

}

void Tile::draw(sf::RenderTarget &renderTarget) {
    renderTarget.draw(shape);
}
