#include "MainMenuWindow.h"


MainMenuWindow::MainMenuWindow()
: window(sf::VideoMode(1920, 1080), "theBindingOfOriOfHadesMainMenu", sf::Style::Default) {
    windowHandle = window.getSystemHandle();
    window.setFramerateLimit(60);
}

