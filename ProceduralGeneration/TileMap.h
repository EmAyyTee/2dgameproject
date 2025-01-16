#pragma once
#include <memory>
#include <vector>

#include "Floor.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "../TextureLoader.h"
#include "../GreenSlime.h"
#include "../BigGreenSlime.h"



class TileMap {
    float gridSizeF;
    sf::Vector2u maxSize;
    std::vector<std::vector<std::vector<Floor*>>> map;
    sf::Texture texture;



public:

    TileMap(float gridSize, unsigned width, unsigned height);

    sf::Vector2i worldToCell(const sf::Vector2i& worldPosition);

    void update();
    void draw(sf::RenderTarget& renderTarget);
    void setTile(int gridX, int gridY, const Floor& tile);
    void removeTiles();
    void spawnEnemies(int &enemiesCount, int &aliveEnemiesCount,int &spawnPoints, sf::RenderWindow *renderWindow,
                      std::vector<GreenSlime> &greenSlimes,
                      std::shared_ptr<TextureLoader> textureLoader);
    void checkIfPlayerIsOnMap(Player &player);
    void saveTileMap(std::ofstream &file);
    void loadTileMap(std::ifstream &file);

};

