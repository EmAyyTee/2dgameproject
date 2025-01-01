#pragma once
#include "MainWindow.h"
#include "TextureLoader.h"

class Engine{
    MainWindow& window;

public:
    Engine(MainWindow& windowRef);
    void run();
};
