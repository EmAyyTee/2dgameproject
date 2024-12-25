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
    Player player({100.0f, 100.0f}, &texture_loader.playerTextures);

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }

        player.update(1.0f/ 60.0f);

        renderWindow.clear();
        player.draw(renderWindow);
        renderWindow.display();
    }
}