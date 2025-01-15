#pragma once
#include <fstream>
#include <memory>
#include <random>
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "../TextureLoader.h"
#include "../GreenSlime.h"
#include "../BigGreenSlime.h"
#include "../SmallGreenSlime.h"



class Floor {
protected:
    sf::RectangleShape rectangle;
    sf::Sprite sprite;
    bool isBlocked;
    bool isVisible;

public:
    sf::Clock canISpawnHere;
    sf::Texture texture;

    Floor(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& textureRect);

    Floor(const Floor& other);

    void update();

    void draw(sf::RenderTarget& renderTarget);

    void setVisible(bool visible);

    bool getVisible() const;

    void setBlocked(bool blocked);

    bool getBlocked() const;

    void setTexture(sf::Texture& texture, sf::IntRect textureRect);

    void setPosition(sf::Vector2f position);

    void spawnAnEnemy(int &spawnPoints, sf::RenderWindow *renderWindow,
                      std::vector<GreenSlime> &greenSlimes,
                      std::shared_ptr<TextureLoader> textureLoader);

    void update(float deltaTime);

    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);

    sf::Texture& getTexture();
};
