#pragma once
#include "MainWindow.h"
#include "GameState.h"
#include <fstream>


class Engine{
    MainWindow* window = nullptr;

    std::map<std::string, sf::Keyboard::Key> supportedKeys;
    std::ifstream keySettings;

    void initKeys();

public:
    Engine(MainWindow& windowRef);
    void run(MainWindow& windowRef);

private:
    GameState gameState;
    bool shouldTheGameClose = false;
};
