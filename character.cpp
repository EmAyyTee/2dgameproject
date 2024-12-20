#include "character.h"
#include "SFML/Graphics/RenderWindow.hpp"

character::character() {
    texture.loadFromFile("PlayerCharacter/Archer/IdleNoCelling.png");
    sprite.setTextureRect(sf::IntRect(x, y, 128, 74));
    sprite.setTexture(texture);
}
