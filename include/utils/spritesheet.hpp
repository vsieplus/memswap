// Wrapper class for a spritesheet

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <unordered_map>
#include <string>
#include <any>

#include <SDL.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>

#include "utils/texture.hpp"

class SpriteSheet {
    private:
        // first global ID which appears on this spritesheet
        int firstGID;

        // the spritesheet texture
        Texture spritesheetTexture;

        // spritesheet clips, key: tile GID, val: SDL_Rect representing clip
        std::unordered_map<int, SDL_Rect> spritesheetClips;

        // (non-empty) tile properties, as stored in the tiledmap data
        // key: tile ID, value: map of properties (prop. names -> values)
        std::unordered_map<int, std::unordered_map<std::string, std::any>> tileProperties;

        void loadTileProperties(const tmx::Tileset::Tile & tile);

    public:
        SpriteSheet(std::string mapPath, std::string tilesetName, SDL_Renderer * renderer);

        void loadSpritesheet(std::string mapPath, std::string tilesetName, 
            SDL_Renderer * renderer);

        // get a specified property value for a given tile
        template <class T>
        T getPropertyValue(int tileID, std::string propertyName) const {
            return std::any_cast<T>(tileProperties.at(tileID).at(propertyName));
        }

        // get the clip in this spritesheet for the given tile (as SDL_Rect) 
        const SDL_Rect & getTileClip(int tileID) const;

        SDL_Texture * getTexture() const;

        int getFirstGID() const;
};

#endif // SPRITESHEET_HPP