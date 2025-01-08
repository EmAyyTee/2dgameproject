#include "BetterClock.h"

BetterClock::BetterClock()
    :pausedTime(sf::Time::Zero), isActive(false){
}

void BetterClock::start() {
    if (!isActive) {
        clock.restart();
        isActive = true;
    }
}

void BetterClock::stop() {
    if (isActive) {
        pausedTime += clock.getElapsedTime();
        isActive = false;
    }
}

sf::Time BetterClock::getClockTime() const {
    if(isActive) {
        return pausedTime + clock.getElapsedTime();
    }
    return pausedTime;
}

void BetterClock::restart() {
    clock.restart();
    pausedTime = sf::Time::Zero;
    isActive = false;
}
