#include "MainWindow.h"

MainWindow::MainWindow()
    : window(sf::VideoMode(800, 600), "theBindingOfOriOfHades", sf::Style::Default) {
    windowHandle = window.getSystemHandle();
    window.setFramerateLimit(60);
}

    sf::RenderWindow& MainWindow::getWindow() {
        return window;
    }

