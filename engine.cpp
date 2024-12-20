#include "Engine.h"
#include "SFML/Window/Event.hpp"

Engine::Engine(MainWindow& windowRef)
    : window(windowRef) {
}

void Engine::run() {
    sf::RenderWindow& renderWindow = window.getWindow();

    while (renderWindow.isOpen()) {
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }
        renderWindow.clear();
        renderWindow.display();
    }
}
