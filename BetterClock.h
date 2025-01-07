#pragma once
#include "SFML/System/Clock.hpp"

class BetterClock {
    sf::Clock clock;
    sf::Time pausedTime;
    bool isActive;

    public:
    BetterClock();

    void start();

    void stop();

    sf::Time getClockTime() const;

    void restart();
};
