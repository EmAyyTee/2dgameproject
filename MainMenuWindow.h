#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/WindowHandle.hpp"

class MainMenuWindow {
    sf::RenderWindow window;
    sf::WindowHandle windowHandle;
public:
    MainMenuWindow();
};
