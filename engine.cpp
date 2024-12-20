#include "Engine.h"
#include "Player.h"
#include "SFML/Window/Event.hpp"

Engine::Engine(MainWindow& windowRef)
    : window(windowRef) {
}

void Engine::run() {
    sf::RenderWindow& renderWindow = window.getWindow();
    sf::Event event;
    Player player;

    while (renderWindow.isOpen()) {


        while (renderWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f position = player.sprite.getPosition();
            player.sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, -10)));
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f position = player.sprite.getPosition();
            player.sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, 10)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2f position = player.sprite.getPosition();
            player.sprite.setPosition(sf::Vector2f(position + sf::Vector2f(-10, 0)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sf::Vector2f position = player.sprite.getPosition();
            player.sprite.setPosition(sf::Vector2f(position + sf::Vector2f(10, 0)));
        }

        renderWindow.clear();
        renderWindow.draw(player.sprite);
        renderWindow.display();
    }
}
