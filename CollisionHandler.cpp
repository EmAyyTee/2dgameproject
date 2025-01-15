#include "CollisionHandler.h"

#include <complex>

bool CollisionHandler::checkCollision(sf::FloatRect &rectA, sf::FloatRect &rectB) {
    return rectA.intersects(rectB);
}

void CollisionHandler::handleGreenSlimeCollision(GreenSlime &slime1, GreenSlime &slime2) {
    sf::FloatRect boundsOfSlime1 = slime1.getHitBox().getGlobalBounds();
    sf::FloatRect boundsOfSlime2 = slime2.getHitBox().getGlobalBounds();

    sf::Vector2f delta = sf::Vector2f(boundsOfSlime1.left + boundsOfSlime1.width / 2 - (boundsOfSlime2.left + boundsOfSlime2.width / 2),
        boundsOfSlime1.top + boundsOfSlime1.height / 2 - (boundsOfSlime2.top + boundsOfSlime2.height / 2));

    float lenght = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (lenght == 0.0f) {
        lenght = 0.01f;
    }

    sf::Vector2f direction = delta / lenght;

    float overlap = (boundsOfSlime1.width / 2 + boundsOfSlime2.width / 2) - lenght;

    if(overlap > 0.0f) {
        slime1.setPosition(slime1.getPosition() + direction * (overlap / 2.0f));
        slime2.setPosition(slime2.getPosition() - direction * (overlap / 2.0f));
    }

}

void CollisionHandler::handleGreenSlimeCollision(BigGreenSlime &slime1, BigGreenSlime &slime2) {
    sf::FloatRect boundsOfSlime1 = slime1.getHitBox().getGlobalBounds();
    sf::FloatRect boundsOfSlime2 = slime2.getHitBox().getGlobalBounds();

    sf::Vector2f delta = sf::Vector2f(boundsOfSlime1.left + boundsOfSlime1.width / 2 - (boundsOfSlime2.left + boundsOfSlime2.width / 2),
        boundsOfSlime1.top + boundsOfSlime1.height / 2 - (boundsOfSlime2.top + boundsOfSlime2.height / 2));

    float lenght = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (lenght == 0.0f) {
        lenght = 0.01f;
    }

    sf::Vector2f direction = delta / lenght;

    float overlap = (boundsOfSlime1.width / 2 + boundsOfSlime2.width / 2) - lenght;

    if(overlap > 0.0f) {
        slime1.setPosition(slime1.getPosition() + direction * (overlap / 2.0f));
        slime2.setPosition(slime2.getPosition() - direction * (overlap / 2.0f));
    }

}

void CollisionHandler::checkGreenSlimesCollisions(std::vector<GreenSlime> &greenSlimes) {
    for (size_t i = 0; i < greenSlimes.size(); ++i) {
        for (size_t j = i + 1; j < greenSlimes.size(); ++j) {
            sf::FloatRect slimeA = greenSlimes[i].getHitBox().getGlobalBounds();
            sf::FloatRect slimeB = greenSlimes[j].getHitBox().getGlobalBounds();

            if (checkCollision(slimeA, slimeB)) {
                handleGreenSlimeCollision(greenSlimes[i], greenSlimes[j]);
            }
        }
    }
}

void CollisionHandler::checkGreenSlimesCollisions(std::vector<BigGreenSlime> &greenSlimes) {
    for (size_t i = 0; i < greenSlimes.size(); ++i) {
        for (size_t j = i + 1; j < greenSlimes.size(); ++j) {
            sf::FloatRect slimeA = greenSlimes[i].getHitBox().getGlobalBounds();
            sf::FloatRect slimeB = greenSlimes[j].getHitBox().getGlobalBounds();

            if (checkCollision(slimeA, slimeB)) {
                handleGreenSlimeCollision(greenSlimes[i], greenSlimes[j]);
            }
        }
    }
}