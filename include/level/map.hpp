// Header file for map class

#ifndef MAP_HPP
#define MAP_HPP

#include <utility>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>

#include "level/tile.hpp"
#include "utils/spritesheet.hpp"

class MemSwap;

class Level;

class Map {
    private:
        int mapWidth, mapHeight;         // size of map in tiles
        int tileWidth, tileHeight;       // size of tiles in pixels

        int renderX, renderY;            // x,y on the screen to render map

        // A vector holding the background tiles for the map
        std::vector<Tile> mapTiles;

        // store spritesheets used by this map  (key: ss first GID, val: ptr->ss)
        std::unordered_map<int, std::shared_ptr<SpriteSheet>> mapSpritesheets;

        // store tile GIDs for parity tiles (key: parity, val: Tile ID)
        std::unordered_map<int, int> parityTileIDs;

    public:
        // strings used to interface with tiledmap properties/labels
        const static std::string BG_LAYER_NAME, ENTITY_LAYER_NAME, PARITY_PROP;

        Map();
        Map(std::string tiledMapPath, SDL_Renderer * renderer, Level * level, 
            MemSwap * game);

        void update(Level * level);
        void render(SDL_Renderer * renderer) const;

        // Load map for the level
        void loadMap(std::string tiledMapPath, SDL_Renderer * renderer, Level * level, MemSwap * game);

        // add background tiles to the map from the given tileLayer
        void addBGTiles(const tmx::TileLayer * tileLayer, Level * level,
            MemSwap * game);

        // Check if a tile is in bounds
        bool inBounds(int x, int y) const;

        // Update bg tiles when the specified movement occurs
        void flipTiles(int tileX, int tileY, int moveDir, int playerParity,
            Level * level);

        // Get parity of tile at the specified grid location
        int getTileParity(int x, int y) const;

        int getRenderX() const;
        int getRenderY() const;
};

#endif // MAP_HPP
