#include "Engine.h"

#include "Button.h"
#include "Player.h"
#include "TextureLoader.h"
#include "GreenSlime.h"
#include "SFML/Window/Event.hpp"



Engine::Engine()
    : gameState(GameState::MainMenu) {
    initKeys();

}
void Engine::run(MainWindow& windowRef) {
    auto textureLoader = std::make_shared<TextureLoader>();

    if (gameState == GameState::MainMenu) {
        sf::RenderWindow& renderWindow = windowRef.getWindow();
        sf::Event event;

        Button playButton;

        while (renderWindow.isOpen()) {
            while (renderWindow.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    renderWindow.close();
                }
            }
            renderWindow.clear();
            playButton.buttonDraw(renderWindow);
            renderWindow.display();
        }
    }
    else if (gameState == GameState::Running) {
        sf::RenderWindow& renderWindow = windowRef.getWindow();
        sf::Event event;

        Player player({static_cast<float>(renderWindow.getSize().x/2) -64,static_cast<float>(renderWindow.getSize().y/2) - 64 },
            std::make_shared<std::vector<std::pair<int, sf::Texture>>>(textureLoader -> playerTextures),
            &renderWindow, &supportedKeys);

        GreenSlime greenSlime({100.0f, 100.0f}, std::make_shared<std::vector<std::pair<int,
            sf::Texture>>>(textureLoader -> greenSlimeTextures), &renderWindow);

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
}
void Engine::initKeys() {
    std::ifstream keySettings("playerKeyboardSettings.ini");
     supportedKeys.emplace("walkLeft", sf::Keyboard::A);
     supportedKeys.emplace("walkRight", sf::Keyboard::D);
     supportedKeys.emplace("walkUp", sf::Keyboard::W);
     supportedKeys.emplace("walkDown", sf::Keyboard::S);
}
