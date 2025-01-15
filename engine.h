#pragma once
#include "MainWindow.h"
#include "GameState.h"
#include <fstream>

#include "BigGreenSlime.h"
#include "CollisionHandler.h"
#include "GreenSlime.h"
#include "PlayButton.h"
#include "PlayerArrow.h"
#include "PlayerHud.h"
#include "TextButton.h"
#include "PlayerUpgrades/DamageUpgrade.h"
#include "PlayerUpgrades/DashUpgrade.h"
#include "PlayerUpgrades/HealthUpgrade.h"
#include "PlayerUpgrades/PiercingUpgrade.h"
#include "PlayerUpgrades/SpeedUpgrade.h"
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


    //Long list of upgrades
    PiercingUpgrade piercing_upgrade;
    DamageUpgrade damage_upgrade;
    SpeedUpgrade speed_upgrade;
    HealthUpgrade health_upgrade;
    DashUpgrade dash_upgrade;

    bool upgradeSelected = false;
    //The end of a long list of upgrades

    TileMap map, wallMap;

private:
    GameState gameState;
    float gridSize;
    bool shouldTheGameClose = false;
    std::vector<PlayerArrow> arrows;
    std::vector<PlayerArrow> remainingArrows;
    std::vector<GreenSlime> greenSlimes;
    std::vector<sf::Vector2f> greenSlimesFromBigSlimesPositions;
    size_t greenSlimesFromBigSlimesSize;
    sf::Vector2u mousePosOnGrid;
    sf::View view;
    int enemiesCount = 0;
    int aliveEnemiesCount;
    int spawningPoints;
    std::vector<TextButton> allUpgrades;

    size_t loadedGreenSlimeCount;
    size_t loadedBigGreenSlimeCount;
    bool isGameSaved = false;
    bool shouldTheGameSave;
    Floor floorTile, wallTile;
    PlayButton playButton;

    CollisionHandler enemyCollisionHandler;

    Player player;
    PlayerHud playerHud;

    sf::Texture texture, textureWall;
    std::shared_ptr<TextureLoader> textureLoader;

    sf::Clock respawnEnemiesClock;
    sf::Clock addSpawnPointsClock;
    sf::Clock pauseClock;

};

sf::Vector2i randomSpawnPosition(sf::RenderWindow& renderWindow);
