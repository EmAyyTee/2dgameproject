#pragma once
#include "MainWindow.h"

class Engine{
    MainWindow& window;

    std::map<std::string, sf::Keyboard::Key> supportedKeys;

    void initKeys();

public:
    Engine(MainWindow& windowRef);
    void run();
};
