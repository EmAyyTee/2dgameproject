#pragma once
#include "MainWindow.h"
#include <fstream>

#include "MainMenuWindow.h"

class Engine{
    MainWindow* window = nullptr;

    std::map<std::string, sf::Keyboard::Key> supportedKeys;
    std::ifstream keySettings;

    void initKeys();

public:
    enum class GameState{
        MainMenu = 0,
        Running = 1
    };

    Engine();
    void run(MainWindow& windowRef, MainMenuWindow &mainMenuWindowRef);

private:
    GameState gameState;
};
