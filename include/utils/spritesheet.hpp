// Wrapper class for a spritesheet

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <unordered_map>
#include <string>
#include <any>
#include <functional>

#include <SDL.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>

#include "utils/texture.hpp"
#include "utils/sprite.hpp"

const std::string TILENAME_PROPERTY = "tilename";

class SpriteSheet {
    private:
        // first global ID which appears on this spritesheet
        int firstGID;

        // the spritesheet texture
        std::shared_ptr<Texture> spritesheetTexture;

        // sprites in the spritesheet, key: hash of tileID, val: Sprite obj.
        std::unordered_map<int, std::shared_ptr<Sprite>> sprites;

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

        // Get the sprite in this sheet with the specified tilename
        std::shared_ptr<Sprite> getSprite(int tileID) const;

        SDL_Texture * getTexture() const;

        int getFirstGID() const;
};

#endif // SPRITESHEET_HPP