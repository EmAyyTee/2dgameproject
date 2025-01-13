#include "Engine.h"

#include <iostream>
#include <random>

#include "Button.h"
#include "Player.h"
#include "TextureLoader.h"
#include "GreenSlime.h"
#include "PlayButton.h"
#include "ProceduralGeneration/RandomWalkDungeonGenerator.h"
#include "ProceduralGeneration/TileMap.h"
#include "SFML/Window/Event.hpp"



Engine::Engine(MainWindow& windowRef)
    : gameState(GameState::MainMenu), gridSize(300.0f), view(windowRef.getWindow().getDefaultView()),
      aliveEnemiesCount(0), floorTile(sf::Texture(), {0,0}, sf::IntRect() ), playButton({0,0}, nullptr, nullptr), player({0,0}, nullptr, nullptr, &supportedKeys), map(gridSize, 400, 400), shouldTheGameSave(false) {
    initKeys();

    textureLoader = std::make_shared<TextureLoader>();

    map = TileMap(gridSize, 400, 400);

    loadSaveFlagForSaves("isTheGameSaved.dat");

    if (!texture.loadFromFile("ProceduralGeneration/Textures/grass.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return;
    }

    floorTile = Floor(texture, {0, 0}, sf::IntRect(0, 0, gridSize, gridSize));

    playButton = PlayButton({static_cast<float>(windowRef.getWindow().getSize().x / 2) - 64,
        static_cast<float>(windowRef.getWindow().getSize().y / 2) - 64},
        std::make_shared<std::vector<std::pair<int, sf::Texture> > >(
        textureLoader->mainMenuPlayButtonTextures),
        &windowRef.getWindow());


    player = Player({
        static_cast<float>(windowRef.getWindow().getSize().x / 2) - 64,
        static_cast<float>(windowRef.getWindow().getSize().y / 2) - 64},
        std::make_shared<std::map<std::string, std::vector<std::pair<int, sf::Texture> > > >(
        textureLoader->allPlayerTextures),
        &windowRef.getWindow(), &supportedKeys);

    RandomWalkDungeonGenerator generator(map, floorTile);
    generator.runProceduralGeneration(map, floorTile);

    run(windowRef);
}

void Engine::run(MainWindow& windowRef) {


    sf::Event event;


    sf::RenderWindow& renderWindow = windowRef.getWindow();

    while (!shouldTheGameClose){
        if (gameState == GameState::MainMenu) {

            PlayButton quitButton({static_cast<float>(windowRef.getWindow().getSize().x / 2 - 32),
        static_cast<float>(windowRef.getWindow().getSize().y / 2 + 64)},
        std::make_shared<std::vector<std::pair<int, sf::Texture> > >(
        textureLoader->mainMenuMenuQuitButtonTextures),
        &windowRef.getWindow());

            quitButton.setTheFrames(0,0,88,88);

            while (renderWindow.isOpen()) {
                while (renderWindow.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        renderWindow.close();
                        shouldTheGameClose = true;
                    }
                }

                playButton.update(1.0f/60.0f, gameState, GameState::Running);
                quitButton.update(1.0f/60.0f, gameState, GameState::Quitting);
                renderWindow.clear();
                playButton.buttonDraw(renderWindow);
                quitButton.buttonDraw(renderWindow);
                renderWindow.display();
                if (gameState != GameState::MainMenu) {
                    break;
                }
            }

        } else if (gameState == GameState::Running) {

            if (isGameSaved) {
                loadGame("saveFile.dat", player);
                isGameSaved = false;
            } else {
                shouldTheGameSave = true;
            }

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
                        saveGame("saveFile.dat", player);
                        saveFlagForSaves("isTheGameSaved.dat");
                        shouldTheGameClose = true;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    gameState =  GameState::Paused;
                }

                renderWindow.clear();
                map.draw(renderWindow);
                player.update(1.0f/ 60.0f, arrows);
                updateTheCamera(player, 1.0f/60.0f, renderWindow);
                renderWindow.setView(view);
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

                if (gameState == GameState::Quitting) {
                    renderWindow.close();
                    saveGame("saveFile.dat", player);
                    saveFlagForSaves("isTheGameSaved.dat");
                    shouldTheGameClose = true;
                } else if (gameState != GameState::Paused) {
                    break;
                }
            }
        } else if (gameState == GameState::Paused) {

            PlayButton quitButton({static_cast<float>(windowRef.getWindow().getSize().x / 2 - 32),
               static_cast<float>(windowRef.getWindow().getSize().y / 2 + 64)},
               std::make_shared<std::vector<std::pair<int, sf::Texture> > >(
               textureLoader->mainMenuMenuQuitButtonTextures),
               &windowRef.getWindow());

            while (renderWindow.isOpen()) {
                while (renderWindow.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        renderWindow.close();
                        shouldTheGameClose = true;
                    }
                }
                playButton.update(1.0f/60.0f, gameState, player, GameState::Running);
                quitButton.update(1.0f/60.0f, gameState, player, GameState::Quitting, true);
                player.shotClock.restart();
                renderWindow.clear();
                map.draw(renderWindow);

                player.draw(renderWindow);

                // for (auto slime = greenSlimes.begin(); slime != greenSlimes.end(); ) {
                //     slime->draw(renderWindow);
                // }

                playButton.buttonDraw(renderWindow);
                quitButton.buttonDraw(renderWindow);

                renderWindow.display();
                if(gameState != GameState::Paused) {
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
    supportedKeys.emplace("exit", sf::Keyboard::Escape);
}

sf::Vector2i randomSpawnPosition(sf::RenderWindow& renderWindow) {
    static std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<int> xDist(0, renderWindow.getSize().x);
    std::uniform_int_distribution<int> yDist(0, renderWindow.getSize().y);



    return {xDist(rng), yDist(rng)};
}
void Engine::updateTheCamera(Player &player, float deltaTime, sf::RenderTarget &target) {
    sf::Vector2f center = view.getCenter();

    sf::Vector2f offset = player.getPosition() - center;

    view.setCenter(center + offset * 5.0f * deltaTime);

    target.setView(view);
}

void Engine::saveGame(const std::string &fileName, Player &player) {
    std::ofstream file(fileName, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't save the game! Access denied\n";
        return;
    }

    file.write(reinterpret_cast<const char*>(&aliveEnemiesCount), sizeof(aliveEnemiesCount));
    file.write(reinterpret_cast<const char*>(&enemiesCount), sizeof(enemiesCount));

    player.saveToFile(file);

    size_t slimeCount = greenSlimes.size();
    file.write(reinterpret_cast<const char*>(&slimeCount), sizeof(slimeCount));
    for (const auto& slime : greenSlimes) {
        slime.saveToFile(file);
    }

    file.close();
    isGameSaved = true;
}

void Engine::loadGame(const std::string &fileName, Player &player) {
    std::ifstream file(fileName, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't load the game! Access denied\n";
        return;
    }

    file.read(reinterpret_cast<char*>(&aliveEnemiesCount), sizeof(aliveEnemiesCount));
    file.read(reinterpret_cast<char*>(&enemiesCount), sizeof(enemiesCount));


    player.loadFromFile(file);

    // size_t slimeCount;
    // file.read(reinterpret_cast<char*>(&slimeCount), sizeof(slimeCount));
    // greenSlimes.resize(slimeCount);
    // for (auto& slime : greenSlimes) {
    //     slime.loadFromFile(file);
    // }

    file.close();
    isGameSaved = false;
}

void Engine::saveFlagForSaves(const std::string &fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't save the saves! Access denied\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(&isGameSaved), sizeof(isGameSaved));
    file.close();
}

void Engine::loadSaveFlagForSaves(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't check if there are saves! Access denied\n";
        return;
    }
    file.read(reinterpret_cast<char*>(&isGameSaved), sizeof(isGameSaved));
    file.close();
}
