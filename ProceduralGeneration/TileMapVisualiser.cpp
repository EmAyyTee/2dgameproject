#include "TileMapVisualiser.h"

#include <iostream>
#include <ostream>

TileMapVisualiser::TileMapVisualiser(TileMap& tileMap, Floor &tile)
    : tileMap(tileMap), floorTile(tile) {}



void TileMapVisualiser::paintFloorTiles(const std::vector<sf::Vector2i> &positions) {
    paintTiles(positions, tileMap, floorTile);
}


void TileMapVisualiser::paintTiles(const std::vector<sf::Vector2i>& positions, TileMap& tileMap, const Floor& tile) {
    for (const auto& position : positions) {
        paintSingleTile(tileMap, tile, position);
    }
}

void TileMapVisualiser::paintSingleTile(TileMap& tileMap, const Floor& tile, const sf::Vector2i& position) {
    sf::Vector2i tilePosition = tileMap.worldToCell(position);

    //Use for debug if something goes wrong with the gen

    // std::cout << tilePosition.x << " " << tilePosition.y << std::endl;

    tileMap.setTile(tilePosition.x, tilePosition.y, tile);
}
