#pragma once
#include "MainWindow.h"
#include "GameState.h"
#include <fstream>

#include "GreenSlime.h"
#include "PlayerArrow.h"


class Engine{
    MainWindow* window = nullptr;

    std::map<std::string, sf::Keyboard::Key> supportedKeys;
    std::ifstream keySettings;

    void initKeys();

public:
    Engine(MainWindow& windowRef);
    void run(MainWindow& windowRef);
    void updateTheCamera(Player &player, float deltaTime, sf::RenderTarget &target);

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
};

sf::Vector2i randomSpawnPosition(sf::RenderWindow& renderWindow);
