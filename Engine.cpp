#include "Engine.h"

#include <random>

#include "Button.h"
#include "Player.h"
#include "TextureLoader.h"
#include "GreenSlime.h"
#include "PlayButton.h"
#include "SFML/Window/Event.hpp"



Engine::Engine(MainWindow& windowRef)
    : gameState(GameState::MainMenu), gridSize(100.0f) {
    initKeys();
    run(windowRef);

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
                        shouldTheGameClose = true;
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
                std::make_shared<std::map<std::string, std::vector<std::pair<int, sf::Texture>>>>(textureLoader -> allPlayerTextures),
                &renderWindow, &supportedKeys);


            while (renderWindow.isOpen()) {
                if (aliveEnemiesCount == 0) {
                    enemiesCount++;
                    for (int i = 0; i < enemiesCount; ++i) {
                        greenSlimes.push_back(GreenSlime (static_cast<sf::Vector2f>(randomSpawnPosition(renderWindow)), std::make_shared<std::vector<std::pair<int,
                        sf::Texture>>>(textureLoader -> greenSlimeTextures), &renderWindow));
                    }
                    aliveEnemiesCount = enemiesCount;
                }
                while (renderWindow.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        renderWindow.close();
                        shouldTheGameClose = true;
                    }
                }

                renderWindow.clear();
                player.update(1.0f/ 60.0f, arrows);
                for (auto slime = greenSlimes.begin(); slime != greenSlimes.end(); ) {
                    slime->update(1.0f/60.0f, player);
                    slime->draw(renderWindow);

                    if (!slime->isAlive) {
                        slime = greenSlimes.erase(slime);
                        aliveEnemiesCount--;
                    } else {
                        ++slime;
                    }
                }
                player.draw(renderWindow);

                for (PlayerArrow &arrow : arrows) {
                    arrow.update(1.0f / 60.0f);
                    arrow.draw(renderWindow);

                    if (!arrow.checkArrowLifeTime()) {
                        remainingArrows.push_back(std::move(arrow));
                    }
                }
                arrows = std::move(remainingArrows);
                renderWindow.display();

                if (player.hitPoints == 0){
                    gameState = GameState::MainMenu;
                }

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

sf::Vector2i randomSpawnPosition(sf::RenderWindow& renderWindow) {
    static std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<int> xDist(0, renderWindow.getSize().x);
    std::uniform_int_distribution<int> yDist(0, renderWindow.getSize().y);



    return {xDist(rng), yDist(rng)};
}


