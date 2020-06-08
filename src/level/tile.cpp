// Implementation for tile class

#include "level/level.hpp"
#include "level/tile.hpp"

Tile::Tile(int mapX, int mapY, int tileWidth, int tileHeight, int tileParity,
    std::shared_ptr<Sprite> tileSprite) : tileParity(tileParity), 
    tileSprite(tileSprite) {
    
    renderArea = {mapX, mapY, tileWidth, tileHeight};

    if(tileParity == PARITY_PURPLE) {
        flipped = true;
    }
}

void Tile::update(Level * level) {
    
}

void Tile::render(SDL_Renderer * renderer) const {
    tileSprite->render(renderer, renderArea);
}

// Filp tile's parity, + update sprite
void Tile::flip(std::shared_ptr<Sprite> newTileSprite) {
    tileParity = tileParity == PARITY_GRAY ? PARITY_PURPLE : PARITY_GRAY;
    tileSprite.reset();
    tileSprite = newTileSprite;
    flipped = true;
}

int Tile::getTileParity() const {
    return tileParity;
}

bool Tile::isFlipped() const {
    return flipped;
}