#pragma once
#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RenderWindow.hpp"

class MainWindow {
    sf::RenderWindow window;
    sf::WindowHandle windowHandle;

public:
    MainWindow();
    sf::RenderWindow& getWindow();
};

