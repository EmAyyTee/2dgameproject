#include "TileMap.h"

#include <cmath>
#include <string>

#include "Floor.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
    : gridSizeF(gridSize), maxSize(width, height) {
    map.resize(maxSize.x, std::vector<std::vector<Floor*>>(maxSize.y, std::vector<Floor*>(1, nullptr)));
}


void TileMap::update() {

}

void TileMap::draw(sf::RenderTarget& target) {
    for (size_t x = 0; x < maxSize.x; ++x) {
        for (size_t y = 0; y < maxSize.y; ++y) {
            for (size_t z = 0; z < 1; ++z) {
                if (map[x][y][z] != nullptr) {
                    map[x][y][z]->draw(target);
                }
            }
        }
    }
}

void TileMap::setTile(int gridX, int gridY, const Floor& tile) {
    if (gridX >= 0 && gridX < static_cast<int>(maxSize.x) &&
        gridY >= 0 && gridY < static_cast<int>(maxSize.y)) {
        delete map[gridX][gridY][0];
        map[gridX][gridY][0] = new Floor(tile);
        }
}

sf::Vector2i TileMap::worldToCell(const sf::Vector2i &worldPosition) {
    int x = std::floor(worldPosition.x / gridSizeF);
    int y = std::floor(worldPosition.y / gridSizeF);
    return sf::Vector2i(x, y);
}
