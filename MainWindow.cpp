#include "MainWindow.h"

MainWindow::MainWindow()
    : window(sf::VideoMode::getDesktopMode(), "theBindingOfOriOfHades", sf::Style::Fullscreen) {
    windowHandle = window.getSystemHandle();
    window.setFramerateLimit(60);
}

    sf::RenderWindow& MainWindow::getWindow() {
        return window;
    }

