#include "Engine.h"

#include <iostream>

#include "Player.h"
#include "TextureLoader.h"
#include "GreenSlime.h"
#include "SFML/Window/Event.hpp"



Engine::Engine(MainWindow& windowRef)
    : window(windowRef) {
    initKeys();
}
void Engine::run() {
    sf::RenderWindow& renderWindow = window.getWindow();
    sf::Event event;
    auto textureLoader = std::make_shared<TextureLoader>();
    Player player({static_cast<float>(renderWindow.getSize().x/2) -64,static_cast<float>(renderWindow.getSize().y/2) - 64 },
        std::make_shared<std::vector<std::pair<int, sf::Texture>>>(textureLoader -> playerTextures), &renderWindow, &supportedKeys);
    GreenSlime greenSlime({100.0f, 100.0f}, std::make_shared<std::vector<std::pair<int, sf::Texture>>>(textureLoader -> greenSlimeTextures), &renderWindow);

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }

        player.update(1.0f/ 60.0f);
        greenSlime.update(1.0f/ 60.0f, player);

        renderWindow.clear();
        player.draw(renderWindow);
        greenSlime.draw(renderWindow);
        renderWindow.display();
    }
}
void Engine::initKeys() {
    supportedKeys.emplace("walkLeft", sf::Keyboard::A);
    supportedKeys.emplace("walkRight", sf::Keyboard::D);
    supportedKeys.emplace("walkUp", sf::Keyboard::W);
    supportedKeys.emplace("walkDown", sf::Keyboard::S);
}
