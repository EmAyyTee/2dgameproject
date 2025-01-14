#include "TileMap.h"

#include <cmath>
#include <iostream>
#include <string>

#include "Floor.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
    : gridSizeF(gridSize), maxSize(width, height) {
    map.resize(maxSize.x, std::vector(maxSize.y, std::vector<Floor*>(1, nullptr)));
    texture.loadFromFile("ProceduralGeneration/Textures/grass.png");
}


void TileMap::update() {

}

void TileMap::draw(sf::RenderTarget& target) {
    for (size_t x = 0; x < maxSize.x; ++x) {
        for (size_t y = 0; y < maxSize.y; ++y) {
            for (size_t z = 0; z < 1; ++z) {
                if (map[x][y][z] != nullptr) {
                    // std::cout << "Drawing tile at grid (" << x << ", " << y << ")" << std::endl;
                    map[x][y][z]->draw(target);
                }
            }
        }
    }
}

void TileMap::setTile(int gridX, int gridY, const Floor& tile) {
    if (gridX >= 0 && gridX < static_cast<int>(maxSize.x) &&
        gridY >= 0 && gridY < static_cast<int>(maxSize.y)) {

        //Use for debug if something goes wrong with the gen

        // std::cout << "Setting tile at grid (" << gridX << ", " << gridY << ") with position ("
        //           << gridX * gridSizeF << ", " << gridY * gridSizeF << ")" << std::endl;
        // delete map[gridX][gridY][0];


        //Use for debug if something goes wrong with the gen

        map[gridX][gridY][0] = new Floor(texture,{0,0}, sf::IntRect(0,0, gridSizeF,gridSizeF));
        // std::cout << "Creted a new floor! " << std::endl;
        map[gridX][gridY][0]->setPosition({gridX * gridSizeF, gridY * gridSizeF});
        // std::cout << "Pos of the floor: " << gridX * gridSizeF << "\n" << gridY * gridSizeF << "\n";
        } else {
            // std::cout << "Grid position out of bounds: (" << gridX << ", " << gridY << ")" << std::endl;
        }
}

sf::Vector2i TileMap::worldToCell(const sf::Vector2i &worldPosition) {
    int x = std::floor(worldPosition.x);
    int y = std::floor(worldPosition.y);
    return sf::Vector2i(x, y);
}

void TileMap::saveTileMap(std::ofstream &file) {
    if (!file.is_open()) {
        std::cerr << "Failed to open the file for saving TileMap!\n";
        return;
    }

    file.write(reinterpret_cast<const char*>(&gridSizeF), sizeof(gridSizeF));
    file.write(reinterpret_cast<const char*>(&maxSize.x), sizeof(maxSize.x));
    file.write(reinterpret_cast<const char*>(&maxSize.y), sizeof(maxSize.y));

    for (size_t x = 0; x < maxSize.x; ++x) {
        for (size_t y = 0; y < maxSize.y; ++y) {
            if (map[x][y][0] != nullptr) {
                bool exists = true;
                file.write(reinterpret_cast<const char*>(&exists), sizeof(exists));
                map[x][y][0]->saveToFile(file);
            } else {
                bool exists = false;
                file.write(reinterpret_cast<const char*>(&exists), sizeof(exists));
            }
        }
    }
}

void TileMap::loadTileMap(std::ifstream &file) {
    if (!file.is_open()) {
        std::cerr << "Failed to open the file for loading TileMap!\n";
        return;
    }
    file.read(reinterpret_cast<char*>(&gridSizeF), sizeof(gridSizeF));
    file.read(reinterpret_cast<char*>(&maxSize.x), sizeof(maxSize.x));
    file.read(reinterpret_cast<char*>(&maxSize.y), sizeof(maxSize.y));

    map.clear();
    map.resize(maxSize.x, std::vector(maxSize.y, std::vector<Floor*>(1, nullptr)));

    for (size_t x = 0; x < maxSize.x; ++x) {
        for (size_t y = 0; y < maxSize.y; ++y) {
            bool exists;
            file.read(reinterpret_cast<char*>(&exists), sizeof(exists));

            if (exists) {
                map[x][y][0] = new Floor(texture, {0, 0}, sf::IntRect(0, 0, gridSizeF, gridSizeF));
                map[x][y][0]->loadFromFile(file);
            }
        }
    }
}
