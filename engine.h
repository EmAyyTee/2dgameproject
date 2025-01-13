#pragma once
#include "MainWindow.h"
#include "GameState.h"
#include <fstream>

#include "GreenSlime.h"
#include "PlayButton.h"
#include "PlayerArrow.h"
#include "ProceduralGeneration/Floor.h"
#include "ProceduralGeneration/TileMap.h"


class Engine{
    MainWindow* window = nullptr;

    std::map<std::string, sf::Keyboard::Key> supportedKeys;
    std::ifstream keySettings;

    void initKeys();

public:
    Engine(MainWindow& windowRef);
    void run(MainWindow& windowRef);
    void updateTheCamera(Player &player, float deltaTime, sf::RenderTarget &target);
    void saveGame(const std::string &fileName, Player &player);
    void loadGame(const std::string &fileName, Player &player);
    void saveFlagForSaves(const std::string &fileName);
    void loadSaveFlagForSaves(const std::string &fileName);
    void saveEnemiesCountAndAlive(const std::string &fileName);
    void loadEnemiesCountAndAlive(const std::string &fileName);

private:
    GameState gameState;
    float gridSize;
    bool shouldTheGameClose = false;
    std::vector<PlayerArrow> arrows;
    std::vector<PlayerArrow> remainingArrows;
    std::vector<GreenSlime> greenSlimes;
    sf::Vector2u mousePosOnGrid;
    sf::View view;
    int enemiesCount = 0;
    int aliveEnemiesCount;
    bool isGameSaved;
    bool shouldTheGameSave;
    sf::Clock pauseClock;
    Floor floorTile;
    PlayButton playButton;

    Player player;
    TileMap map;
    sf::Texture texture;
    std::shared_ptr<TextureLoader> textureLoader;

};

sf::Vector2i randomSpawnPosition(sf::RenderWindow& renderWindow);
