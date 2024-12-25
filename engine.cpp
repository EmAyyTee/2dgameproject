#include "Engine.h"
#include "Player.h"
#include "TextureLoader.h"
#include "SFML/Window/Event.hpp"



Engine::Engine(MainWindow& windowRef)
    : window(windowRef) {
}

void Engine::run() {
    sf::RenderWindow& renderWindow = window.getWindow();
    sf::Event event;
    TextureLoader texture_loader;
    Player player({100.0f, 100.0f});

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }

        sf::Vector2f direction = {0.0f, 0.0f};
        character::AnimationType animationType = character::AnimationType::PlayerIdle;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            animationType = character::AnimationType::PlayerWalkingLeft;
            direction.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            animationType = character::AnimationType::PlayerWalkingRight;
            direction.x += 1.0f;
        }

        player.setDirection(direction);
        player.update(1.0f/ 60.0f, animationType);

        renderWindow.clear();
        player.draw(renderWindow);
        renderWindow.display();
    }
}