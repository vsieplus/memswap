// Implementation for tile class

#include "level/level.hpp"
#include "level/tile.hpp"

Tile::Tile(int mapX, int mapY, int tileWidth, int tileHeight, int tilesetFirstGID,
        int tilesetID, int tileParity) : x(mapX), y(mapY), 
        tilesetFirstGID(tilesetFirstGID), tilesetID(tilesetID), 
        tileParity(tileParity) {
    renderArea = {mapX, mapY, tileWidth, tileHeight};

    if(tileParity == PARITY_PURPLE) {
        flipped = true;
    }
}

void Tile::update(Level * level) {
    
}

void Tile::render(SDL_Renderer * renderer, SDL_Texture * tilesetTexture, 
        const SDL_Rect & tilesheetClip) const {
    SDL_RenderCopy(renderer, tilesetTexture, &tilesheetClip, &renderArea);
}

// Filp tile's parity, update tilesetGID.
void Tile::flip(int newTilesetID) {
    tileParity = tileParity == PARITY_GRAY ? PARITY_PURPLE : PARITY_GRAY;
    tilesetID = newTilesetID;
    flipped = true;
}

int Tile::getTilesetFirstGID() const {
    return tilesetFirstGID;
}

int Tile::getID() const {
    return tilesetID;
}

int Tile::getTileParity() const {
    return tileParity;
}

bool Tile::isFlipped() const {
    return flipped;
}