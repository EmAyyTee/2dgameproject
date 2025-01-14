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
      aliveEnemiesCount(0), enemiesCount(5),spawningPoints(5), floorTile(sf::Texture(),
          {0,0}, sf::IntRect() ),
playButton({0,0}, nullptr, nullptr),
player({0,0}, nullptr, nullptr, &supportedKeys),
map(gridSize, 400, 400), shouldTheGameSave(false),
playerHud(player.hitPoints, player.score){
    initKeys();

    textureLoader = std::make_shared<TextureLoader>();

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
                player.shotClock.restart();
                playButton.update(1.0f/60.0f, gameState, player,GameState::Running);
                quitButton.update(1.0f/60.0f, gameState, player, GameState::Quitting, true);
                updateTheCamera(player, 1.0f/60.0f, renderWindow);
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
                std::cout << "Im loading the game and changing is game saved to false!\n";
                isGameSaved = false;
            }
            // std::cout << "After loading, slime array has size of: "<< greenSlimes.size() << "\n";

            while (renderWindow.isOpen()) {
                if(addSpawnPointsClock.getElapsedTime().asSeconds()> 2.0f) {
                    spawningPoints++;
                    addSpawnPointsClock.restart();
                }

                if (respawnEnemiesClock.getElapsedTime().asSeconds() > 4.0f) {
                        enemiesCount++;
                    if(aliveEnemiesCount == 0){
                        map.spawnEnemies(enemiesCount, aliveEnemiesCount,spawningPoints, &renderWindow, greenSlimes, textureLoader);
                    }
                    else if (spawningPoints > 0 ){
                        int temporaryEnemiesCount = enemiesCount - aliveEnemiesCount;
                        map.spawnEnemies(temporaryEnemiesCount, aliveEnemiesCount,spawningPoints, &renderWindow, greenSlimes, textureLoader);
                    }
                    respawnEnemiesClock.restart();

                    shouldTheGameSave = true;

                }
                while (renderWindow.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        renderWindow.close();
                        saveGame("saveFile.dat", player);
                        saveFlagForSaves("isTheGameSaved.dat");
                        saveEnemiesCountAndAlive("enemisCountAndAlive.dat");
                        shouldTheGameClose = true;
                    }
                }

                renderWindow.clear();
                map.draw(renderWindow);
                player.update(1.0f/ 60.0f, arrows);
                updateTheCamera(player, 1.0f/60.0f, renderWindow);
                playerHud.update(player);
                playerHud.draw(renderWindow);
                renderWindow.setView(view);

                enemyCollisionHandler.checkGreenSlimesCollisions(greenSlimes);

                for (auto slime = greenSlimes.begin(); slime != greenSlimes.end(); ) {
                    slime->update(1.0f/60.0f, player);
                    slime->draw(renderWindow);

                    if (!slime->isAlive) {
                        if(slime->slimeVariant == 0) {
                            slime = greenSlimes.erase(slime);
                            aliveEnemiesCount--;
                            player.addToScore(2);
                        } else if (slime->slimeVariant == 1) {
                            aliveEnemiesCount--;
                            player.addToScore(6);
                            sf::Vector2f offset = {2.0f, 2.0f};
                            for (size_t t = 0; t < 2; t++) {
                                greenSlimesFromBigSlimesPositions.push_back(slime->getPosition() + offset);
                                greenSlimesFromBigSlimesSize++;
                                offset = {-2.0f, -2.0f};
                            }
                            slime = greenSlimes.erase(slime);
                        }else if (slime->slimeVariant == 2) {
                            slime = greenSlimes.erase(slime);
                            aliveEnemiesCount--;
                            player.addToScore(1);
                        }

                    } else {
                        ++slime;
                    }
                }
                if (greenSlimesFromBigSlimesPositions.size() > 0) {
                    for (auto & position: greenSlimesFromBigSlimesPositions) {
                        greenSlimes.push_back(GreenSlime ({position.x, position.y}, std::make_shared<std::vector<std::pair<int,
                                    sf::Texture>>>(textureLoader -> greenSlimeTextures), &renderWindow));
                        aliveEnemiesCount++;
                    }
                }
                greenSlimesFromBigSlimesPositions.clear();

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

                if (player.hitPoints <= 0){
                    gameState = GameState::MainMenu;
                    aliveEnemiesCount = 0;
                    enemiesCount = 5;
                    greenSlimes.clear();
                    shouldTheGameSave = false;
                    isGameSaved = false;
                    player.hitPoints = 10;
                    player.setPosition(sf::Vector2f(static_cast<float>(windowRef.getWindow().getSize().x / 2) - 64,
                    static_cast<float>(windowRef.getWindow().getSize().y / 2) - 64));
                    map.removeTiles();
                    map = TileMap (gridSize, 400, 400);
                    RandomWalkDungeonGenerator generator(map, floorTile);
                    generator.runProceduralGeneration(map, floorTile);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& pauseClock.getElapsedTime().asSeconds() > 0.1f) {
                        gameState = GameState::Paused;
                    pauseClock.restart();
                }

                if (gameState != GameState::Running) {
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

                for (auto slime = greenSlimes.begin(); slime != greenSlimes.end(); ++slime) {
                    slime->draw(renderWindow);
                }

                playButton.buttonDraw(renderWindow);
                quitButton.buttonDraw(renderWindow);

                renderWindow.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape )&& pauseClock.getElapsedTime().asSeconds() > 0.1f) {
                    gameState = GameState::Running;
                    pauseClock.restart();
                }
                if(gameState != GameState::Paused) {
                    break;
                }
            }
        }
        if (gameState == GameState::Quitting && shouldTheGameSave) {
            renderWindow.close();
            saveGame("saveFile.dat", player);
            saveFlagForSaves("isTheGameSaved.dat");
            saveEnemiesCountAndAlive("enemisCountAndAlive.dat");
            shouldTheGameClose = true;
        }
        else if (gameState == GameState::Quitting) {
            renderWindow.close();
            saveFlagForSaves("isTheGameSaved.dat");
            enemiesCount = 0;
            aliveEnemiesCount = 0;
            shouldTheGameClose = true;
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

    //Used for testing, remember to delete later!!!

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

    player.saveToFile(file);
    std::cout << "I save the player!\n";


    for (const auto& slime : greenSlimes) {
        slime.saveToFile(file);
        std::cout << "I save a slime!\n";
    }


    map.saveTileMap(file);

    file.close();
    isGameSaved = true;
}

void Engine::loadGame(const std::string &fileName, Player &player) {
    std::ifstream file(fileName, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't load the game! Access denied\n";
        return;
    }
    loadEnemiesCountAndAlive("enemisCountAndAlive.dat");
    player.loadFromFile(file);
    std::cout << "I load the player!\n";

    std::cout << "After loading enemies count is: " << aliveEnemiesCount;

    greenSlimes.clear();
    std::cout << "Slime array has size of: " << greenSlimes.size() << "\n";
    std::cout << "Alive enemies count is: " << aliveEnemiesCount << "\n";


    for (int i = 0; i < aliveEnemiesCount; i++) {
        std::cout << "I try loading a slime!\n";

        GreenSlime temporarySlime (sf::Vector2f{0,0}, std::make_shared<std::vector<std::pair<int,
                        sf::Texture>>>(textureLoader -> greenSlimeTextures), &window->getWindow());
        temporarySlime.loadFromFile(file);

        // BigGreenSlime temporaryBigSlime (sf::Vector2f{0,0}, std::make_shared<std::vector<std::pair<int,
        //                 sf::Texture>>>(textureLoader -> greenSlimeTextures), &window->getWindow());
        // temporaryBigSlime.loadFromFile(file);

        std::cout << "Loaded slime has: " << temporarySlime.hitPoints << " \n";
        greenSlimes.push_back(temporarySlime);

        // else if(temporaryBigSlime.slimeVariant == 1) {
        //     std::cout << "Loaded slime has: " << temporaryBigSlime.hitPoints << " \n";
        //     bigGreenSlimes.push_back(temporaryBigSlime);
        // }
    }

    map.loadTileMap(file);

    file.close();
    isGameSaved = false;
}

void Engine::saveEnemiesCountAndAlive(const std::string &fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't load the game! Access denied\n";
        return;
    }

    file.write(reinterpret_cast<const char*>(&aliveEnemiesCount), sizeof(aliveEnemiesCount));
    file.write(reinterpret_cast<const char*>(&enemiesCount), sizeof(enemiesCount));
    file.close();
}


void Engine::loadEnemiesCountAndAlive(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Can't load the game! Access denied\n";
        return;
    }

    // For Uni proffessor: reinterpret_cast found here:
    //https://en.cppreference.com/w/cpp/language/reinterpret_cast
    // And this is where I found out it was what I needed:
    //https://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast

    file.read(reinterpret_cast<char*>(&aliveEnemiesCount), sizeof(aliveEnemiesCount));
    file.read(reinterpret_cast<char*>(&enemiesCount), sizeof(enemiesCount));

    if (!file) {
        std::cerr << "Error: Failed to read data from file\n";
        aliveEnemiesCount = 0;
        enemiesCount = 0;
        return;
    }
    file.close();
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
