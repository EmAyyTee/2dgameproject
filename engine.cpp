#include "Engine.h"
#include "Player.h"
#include "SFML/Window/Event.hpp"

Engine::Engine(MainWindow& windowRef)
    : window(windowRef) {
}

void Engine::run() {
    sf::RenderWindow& renderWindow = window.getWindow();

    while (renderWindow.isOpen()) {
        sf::Event event;
        Player player;

        while (renderWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }

        renderWindow.clear();
        renderWindow.draw(player.sprite);
        renderWindow.display();
    }
}
