#include "Engine.h"

#include "Button.h"
#include "Player.h"
#include "TextureLoader.h"
#include "GreenSlime.h"
#include "PlayButton.h"
#include "SFML/Window/Event.hpp"



Engine::Engine()
    : gameState(GameState::MainMenu) {
    initKeys();

}
void Engine::run(MainWindow& windowRef) {
    auto textureLoader = std::make_shared<TextureLoader>();

    sf::Event event;

    while (!shouldTheGameClose){
        if (gameState == GameState::MainMenu) {
            sf::RenderWindow& renderWindow = windowRef.getWindow();

            PlayButton playButton({static_cast<float>(renderWindow.getSize().x/2) -64,static_cast<float>(renderWindow.getSize().y/2) - 64 },
                std::make_shared<std::vector<std::pair<int, sf::Texture>>>(textureLoader -> mainMenuPlayButtonTextures),
                &renderWindow);

            while (renderWindow.isOpen()) {
                while (renderWindow.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        renderWindow.close();
                    }
                }

                playButton.update(1.0f/60.0f, gameState);
                renderWindow.clear();
                playButton.buttonDraw(renderWindow);
                renderWindow.display();
                if (gameState != GameState::MainMenu) {
                    break;
                }
            }

        } else if (gameState == GameState::Running) {

            sf::RenderWindow& renderWindow = windowRef.getWindow();

            Player player({static_cast<float>(renderWindow.getSize().x/2) -64,static_cast<float>(renderWindow.getSize().y/2) - 64 },
                std::make_shared<std::vector<std::pair<int, sf::Texture>>>(textureLoader -> playerTextures),
                &renderWindow, &supportedKeys);

            GreenSlime greenSlime({100.0f, 100.0f}, std::make_shared<std::vector<std::pair<int,
                sf::Texture>>>(textureLoader -> greenSlimeTextures), &renderWindow);

            while (renderWindow.isOpen()) {
                while (renderWindow.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        renderWindow.close();
                        shouldTheGameClose = true;
                    }
                }
                player.update(1.0f/ 60.0f);
                greenSlime.update(1.0f/ 60.0f, player);

                renderWindow.clear();
                player.draw(renderWindow);
                greenSlime.draw(renderWindow);
                renderWindow.display();
                if (gameState != GameState::Running) {
                    break;
                }
            }
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



