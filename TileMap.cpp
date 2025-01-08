#include "TileMap.h"
#include "Tile.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height) {
    gridSizeF = gridSize;
    gridSizeU = static_cast<unsigned>(this->gridSizeF);
    maxSize.x = width;
    maxSize.y = height;
    layers = 1;

    map.resize(maxSize.x);
    for(size_t x = 0; x < maxSize.x; x++) {

        this -> map.push_back(std::vector<std::vector<Tile>>());

        for (size_t y = 0; y < maxSize.y; y++) {

            map.resize(maxSize.y);
            map[x].push_back(std::vector<Tile>());

            for (size_t z = 0; z < layers; z++) {

                map.resize(layers);
                map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));

            }
        }
    }
}

void TileMap::update() {

}

void TileMap::draw(sf::RenderTarget &renderTarget) {
    for (auto &x : map) {
        for (auto &y : x) {
            for (auto &z: y) {
                z.draw(renderTarget);
            }
        }
    }
}

