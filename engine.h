#pragma once
#include "MainWindow.h"

class Engine{
    MainWindow& window;

public:
    Engine(MainWindow& windowRef);
    void run();
};