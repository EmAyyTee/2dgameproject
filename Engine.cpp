#include "Engine.h"
#include "Player.h"
#include "TextureLoader.h"
#include "GreenSlime.h"
#include "SFML/Window/Event.hpp"



Engine::Engine(MainWindow& windowRef)
    : window(windowRef) {
}
void Engine::run() {

    sf::RenderWindow& renderWindow = window.getWindow();
    sf::Event event;
    auto textureLoader = std::make_shared<TextureLoader>();
    Player player({100.0f, 100.0f}, std::make_shared<std::vector<std::pair<int, sf::Texture>>>(textureLoader -> playerTextures), &renderWindow);
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