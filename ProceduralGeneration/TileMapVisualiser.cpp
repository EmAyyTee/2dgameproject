#include "TileMapVisualiser.h"

#include <iostream>
#include <ostream>

TileMapVisualiser::TileMapVisualiser(TileMap& tileMap,TileMap& wallTileMap, Floor &tile, Floor &wallTile)
    : tileMap(tileMap),wallTileMap(wallTileMap), floorTile(tile), wallTop(wallTile) {}



void TileMapVisualiser::paintFloorTiles(const std::vector<sf::Vector2i> &positions) {
    paintTiles(positions, tileMap, floorTile);
}


void TileMapVisualiser::paintTiles(const std::vector<sf::Vector2i>& positions, TileMap& tileMap, Floor& tile) {
    for (const auto& position : positions) {
        paintSingleTile(tileMap, tile, position);
    }
}

void TileMapVisualiser::paintSingleTile(TileMap& tileMap, Floor& tile, const sf::Vector2i& position) {
    sf::Vector2i tilePosition = tileMap.worldToCell(position);

    sf::Texture texture = tile.getTexture();
    tileMap.setTile(tilePosition.x, tilePosition.y, tile, texture);
}

void TileMapVisualiser::paintSingleWall(sf::Vector2i position) {
    paintSingleTile(wallTileMap,wallTop,position);
}
