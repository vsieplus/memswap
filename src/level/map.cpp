// Implementation for map class

#include "memswap.hpp"
#include "entities/player.hpp"
#include "level/level.hpp"
#include "level/map.hpp"

const std::string Map::BG_LAYER_NAME = "background";
const std::string Map::ENTITY_LAYER_NAME = "entities";
const std::string Map::PARITY_PROP = "parity";

Map::Map() {}

// store map path
Map::Map(std::string tiledMapPath) : mapPath(tiledMapPath) {}

// Update each tile in the map
void Map::update(Level * level) {
    for(Tile tile: mapTiles) {
        tile.update(level);
    }
}

void Map::render(SDL_Renderer * renderer) const {
    // Render the background tiles
    for(Tile tile: mapTiles) {
        // Render tile with correct tileset + clip
        auto & ss = mapSpritesheets.at(tile.getTilesetFirstGID());

        tile.render(renderer, ss->getTexture(), ss->getTileClip(tile.getID()));
    }
}

// Load the map for the given level
void Map::loadMap(SDL_Renderer * renderer, Level * level, MemSwap * game) {
    tmx::Map map;

    if(map.load(mapPath)) {
        // update size variables
        auto tilesize = map.getTileSize();
        tileWidth = tilesize.x;
        tileHeight = tilesize.y;
        
        level->updateSize(map, tileWidth, tileHeight);
        mapWidth = level->getGridWidth();
        mapHeight = level->getGridHeight();

        // retrieve pre-loaded spritesheets for the tilesets used in this map
        for(auto & tileset: map.getTilesets()) {
            std::string tilesetName = tileset.getName();
            auto ssPtr = game->getResManager().getSpriteSheet(tilesetName);

            mapSpritesheets.emplace(tileset.getFirstGID(), ssPtr);
        }

        // Get data from each map layer, create necessary tiles/objects
        auto & mapLayers = map.getLayers();
        for (auto & layer : mapLayers) {
            if (layer->getType() != tmx::Layer::Type::Tile) {
                continue; // Do stuff with non-tile layers
            }

            auto * tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());
            
            // process tiles differently depending on the layer we're on
            if(layer->getName() == BG_LAYER_NAME) {
                // Load background tiles
                addBGTiles(tileLayer, level, game);
            } else if (layer->getName() == ENTITY_LAYER_NAME) {
                // load entities into the level
                level->addEntityTiles(tileLayer, mapSpritesheets);
            }
        }
    }
}

// Add background tiles to the map
void Map::addBGTiles(const tmx::TileLayer * tileLayer, Level * level, 
    MemSwap * game) {
    
    auto & layerTiles = tileLayer->getTiles();

    // Compute where to start placing tiles, given map size (center the map)
    renderX = (game->getScreenWidth() / 2) - (mapWidth * tileWidth / 2);
    renderY = (game->getScreenHeight() / 2) - (mapHeight * tileHeight / 2);            
            
    // Iterate through each tile in this layer (top left corner -> down right)
    for(int y = 0; y < mapHeight; y++) {
        for(int x = 0; x < mapWidth; x++) {
            int tileIndex = level->xyToIndex(x,y);

            // Get the GID for the current tile in this layer
            int tileGID = layerTiles[tileIndex].ID;

            // get tileset's firstGID (greatest ID <= ours)
            int tilesetFirstGID = -1;
            for(auto & spritesheet: mapSpritesheets) {
                int currFirstGID = spritesheet.first;
                if(currFirstGID <= tileGID &&  currFirstGID > tilesetFirstGID) {
                    tilesetFirstGID = currFirstGID;
                }
            }

            // no tileset found
            if(tilesetFirstGID == -1) continue;

            // normalize ID to the BG spritesheet
            int tileID = tileGID - tilesetFirstGID;

            // Get position of tile in the map, centered for the given map size 
            auto mapX = renderX + x * tileWidth;
            auto mapY = renderY + y * tileHeight;

            // Get parity of the BG Tile from spritesheet properties
            int tileParity = 
                mapSpritesheets.at(tilesetFirstGID)->getPropertyValue<int>(tileID, PARITY_PROP);
            
            // add to parityTileIDs if not yet complete
            if(parityTileIDs.size() < 2) {                    
                parityTileIDs[tileParity] = tileID;
            }
            
            // Add new tile to mapTiles
            mapTiles.emplace_back(mapX, mapY, tileWidth, tileHeight, 
                tilesetFirstGID, tileID, tileParity);
        }
    }
}

// Check if a tile at the given index is inbounds
bool Map::inBounds(int x, int y) const {
    return (x >= 0 && x <= mapWidth - 1) && (y >= 0 && y <= mapHeight - 1);
}


// Update bg tiles when the specified movement occurs
void Map::flipTiles(int tileX, int tileY, int moveDir, int playerParity, Level * level) {
    // Get indices for all tiles on map surrounding the old pos
    std::list<std::pair<int, int>> tileIndices;

    // none, Up, down, left, right (order matches Direction enum)
    tileIndices.push_back(std::make_pair(tileX, tileY));
/*     tileIndices.push_back(std::make_pair(tileX, tileY - 1));
    tileIndices.push_back(std::make_pair(tileX, tileY + 1));
    tileIndices.push_back(std::make_pair(tileX - 1, tileY));
    tileIndices.push_back(std::make_pair(tileX + 1, tileY));

    // Remove the pair for the tile we moved onto
    auto it = tileIndices.begin();
    advance(it, moveDir);
    tileIndices.erase(it); */

    // For each tile except the one we moved onto, try to call flip if inbounds
    for(auto indices: tileIndices) {
        // Check if in bounds
        if(inBounds(indices.first, indices.second)) {
            Tile & currTile = mapTiles.at(level->xyToIndex(indices.first, indices.second));

            // skip if tile is parity-neutral
            if(currTile.getTileParity() == PARITY_NONE) break;

            // skip tiles already flipped once
            if(currTile.isFlipped()) continue;

            // Flip if parity differs from player's
            if(playerParity != currTile.getTileParity()) {
                currTile.flip(parityTileIDs.at(playerParity));
                break;
            }
        }
    }
}

int Map::getTileParity(int x, int y) const {
    return mapTiles.at(x + y * mapWidth).getTileParity();
}

int Map::getRenderX() const {
    return renderX;
}

int Map::getRenderY() const {
    return renderY;
}