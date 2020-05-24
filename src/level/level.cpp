// Implementation for level class

#include "memswap.hpp"
#include "level/level.hpp"
#include "entities/player.hpp"

const std::string Level::BG_LAYER_NAME = "background";
const std::string Level::ENTITY_LAYER_NAME = "entities";

Level::Level() {}

Level::Level(std::string tiledMapPath, SDL_Renderer * renderer) {
    loadMap(tiledMapPath, renderer);

    // initialize grid
    initGrid();
    grid.emplace(0, std::make_shared<Player>(0, 0, 0, 0, renderer));
}

Level::~Level(){
    grid.clear();
    mapTiles.clear();
}

void Level::initGrid() {
    for(int x = 0; x < gridWidth; x++) {
        for(int y = 0; y < gridHeight; y++) {
            int currIdx = xyToIndex(x,y);
            grid[currIdx] = nullptr;
        }
    }
}

// Event loop
void Level::handleEvents(const Uint8 * keyStates) {
    for(int x = 0; x < gridWidth; x++) {
        for(int y = 0; y < gridHeight; y++) {
            int currIdx = xyToIndex(x,y);
            if(grid[currIdx]) {
                grid[currIdx]->handleEvents(keyStates, this);
            }
        }
    }
}

// Update loop
void Level::update() {
    for(int x = 0; x < gridWidth; x++) {
        for(int y = 0; y < gridHeight; y++) {
            int currIdx = xyToIndex(x,y);
            if(grid[currIdx]) {
                grid[currIdx]->update(this);
            }
        }
    }
}

void Level::render(SDL_Renderer* renderer) const {
    // Render the map
    for(auto & tile: mapTiles) {
        tile.render(renderer);
    } 

    // Render the objs in the grid
    for(int x = 0; x < gridWidth; x++) {
        for(int y = 0; y < gridHeight; y++) {
            int currIdx = xyToIndex(x,y);
            if(grid.at(currIdx)) {
                grid.at(currIdx)->render(renderer);
            }
        }
    }    
}

void Level::loadMap(std::string tiledMapPath, SDL_Renderer * renderer) {
    tmx::Map map;

    if(map.load(tiledMapPath)) {
        updateSize(map);

        // Store level tilesets in map, key: first GID, val: ptr to ts texture      
        std::map<int, std::shared_ptr<SDL_Texture>> tilesets;

        const auto & mapTilesets = map.getTilesets();
        for(const auto & tileset : mapTilesets) {
            // Load the tileset texture

            SDL_Surface * surface = IMG_Load(tileset.getImagePath().c_str());
            
            std::shared_ptr<SDL_Texture> newTexture 
                (SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture);
            
            SDL_FreeSurface(surface);

            tilesets.insert(std::pair<int, std::shared_ptr<SDL_Texture>>
                (tileset.getFirstGID(), newTexture));
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
                addBGTiles(tileLayer, tilesets);
            } else if (layer->getName() == ENTITY_LAYER_NAME) {
                addEntityTiles(tileLayer, tilesets);
            }
        }
    }
}

// Add background tiles to the map
void Level::addBGTiles(const tmx::TileLayer * tileLayer, 
    const std::map<int, std::shared_ptr<SDL_Texture>> & tilesets) {

    auto & layerTiles = tileLayer->getTiles();
            
    // Loop through each tile
    for(auto x = 0; x < gridWidth; x++) {
        for(auto y = 0; y < gridHeight; y++) {
            int tileIndex = xyToIndex(x,y);

            // Get the GID for the current tile in this layer
            int currGID = layerTiles[tileIndex].ID;

            // Find the tileset it is from
            auto tilesetFirstGID = -1;
            for(auto & ts: tilesets) {
                // Pick the last tileset whose first gid is <= ours
                if(ts.first > currGID) break;

                tilesetFirstGID = ts.first;
            }

            // If no tileset has it, continue
            if(tilesetFirstGID == -1) continue;

            // Normalize GID relative to the tileset's first GID
            currGID -= tilesetFirstGID;

            // Get tileset width/height
            auto tilesetWidth = 0;
            auto tilesetHeight = 0;
            SDL_QueryTexture(tilesets.at(tilesetFirstGID).get(), NULL, NULL,
                &tilesetWidth, &tilesetHeight);

            // Get position of tile in the tileset
            auto tilesetX = (currGID % (tilesetWidth/TILE_WIDTH)) * TILE_WIDTH;
            auto tilesetY = (currGID / (tilesetWidth/TILE_HEIGHT)) * TILE_HEIGHT;

            // Get position of tile in the map
            auto mapX = x * TILE_WIDTH;
            auto mapY = y * TILE_HEIGHT;

            mapTiles.emplace_back(mapX, mapY, tilesetX, tilesetY, TILE_WIDTH,
                TILE_HEIGHT, tilesets.at(tilesetFirstGID));
        }
    }
}

// Add entities from tiledmap to entity grid
void Level::addEntityTiles(const tmx::TileLayer * tileLayer, 
    const std::map<int, std::shared_ptr<SDL_Texture>> & tilesets) {

}

// Update size from the given map
void Level::updateSize(const tmx::Map & map) {
    auto map_dimensions = map.getTileCount();

    gridWidth = map_dimensions.x;
    gridHeight = map_dimensions.y;

    auto tilesize = map.getTileSize();
    TILE_WIDTH = tilesize.x;
    TILE_HEIGHT = tilesize.y;

    pixelWidth = TILE_WIDTH * gridWidth;
    pixelHeight = TILE_HEIGHT * gridHeight;
}

int Level::xyToIndex(int x, int y) const {
    return x + y * gridWidth;
}

std::pair<int, int> Level::indexToXY(int index) const {
    int x = index % gridWidth;
    int y = index / gridWidth;
    return std::make_pair(x,y);
}

int Level::getGridWidth() const { 
    return gridWidth;
}

int Level::getGridHeight() const { 
    return gridHeight;
}

int Level::getPixelWidth() const { 
    return pixelWidth;
}

int Level::getPixelHeight() const { 
    return pixelHeight;
}

const std::unordered_map<int, std::shared_ptr<Entity>> & Level::getGrid() {
    return grid;
}

// Move a grid element from start x,y to end
void Level::setGridElement(int startX, int startY, int endX, int endY) {
    grid[xyToIndex(endX, endY)] = std::move(grid[xyToIndex(startX, startY)]);
}