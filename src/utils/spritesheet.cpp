// implementation for spritesheet class

#include "utils/spritesheet.hpp"

SpriteSheet::SpriteSheet(std::string texturePath, SDL_Renderer * renderer,
    int spriteWidth, int spriteHeight) : spritesheetTexture(new Texture()) {
    loadSpritesheet(texturePath, renderer, spriteWidth, spriteHeight);
}

// load directly from an image texture w / specified params
void SpriteSheet::loadSpritesheet(std::string texturePath, SDL_Renderer * renderer,
    int spriteWidth, int spriteHeight) {

    // load the texture
    spritesheetTexture->loadTexture(texturePath, renderer);

    // assumes the texture contains n sprites of size spriteWidth x spriteHeight in one row
    int numSprites = spritesheetTexture->getWidth() / spriteWidth;

    for(int i = 0; i < numSprites; i++) {
        std::shared_ptr<Sprite> tileSprite = 
            std::make_shared<Sprite>(spritesheetTexture,
            (struct SDL_Rect) {i * spriteWidth, 0, spriteWidth, spriteHeight});

        sprites.emplace(i, tileSprite);         
    }

}

SpriteSheet::SpriteSheet(std::string mapPath, std::string tilesetName, 
    SDL_Renderer * renderer) : spritesheetTexture(new Texture()) {
    
    loadSpritesheet(mapPath, tilesetName, renderer);
}
    
// load a spritesheet from a tiledmap
void SpriteSheet::loadSpritesheet(std::string mapPath, std::string tilesetName, 
    SDL_Renderer * renderer) {

    tmx::Map map;

    if(map.load(mapPath)) {
        const auto & readTilesets = map.getTilesets();

        for(const auto & tileset: readTilesets) {
            // check matching tileset names
            if(tileset.getName() == tilesetName) {
                // load the texture
                spritesheetTexture->loadTexture(tileset.getImagePath(), renderer);

                // store first GID
                firstGID = tileset.getFirstGID();

                // get vector of (unique) tiles
                const auto & tiles = tileset.getTiles();

                // construct sprites for each tile in the spritesheet
                for(auto & tile: tiles) {
                    loadTileProperties(tile);

                    // Get position/size of tile in the tileset to create the sprite/clip
                    int tilesetX = tile.imagePosition.x;
                    int tilesetY = tile.imagePosition.y;

                    int tileWidth = tile.imageSize.x;
                    int tileHeight = tile.imageSize.y;

                    std::shared_ptr<Sprite> tileSprite = 
                        std::make_shared<Sprite>(spritesheetTexture,
                        (struct SDL_Rect) {tilesetX, tilesetY, tileWidth, tileHeight});

                    sprites.emplace(tile.ID, tileSprite);               
                }
                break;
            }
        }
    }    
}

void SpriteSheet::loadTileProperties(const tmx::Tileset::Tile & tile) {
    // check/store this tile's properties if nonempty
    auto & properties = tile.properties;

    if(!properties.empty()) {
        std::map<std::string, std::any> propertyMap;

        for(auto & property: properties) {
            std::string propName = property.getName();
            tmx::Property::Type type = property.getType();

            switch(type) {
                case tmx::Property::Type::Boolean:
                    propertyMap.emplace(propName,
                        std::any_cast<bool>(property.getBoolValue()));
                    break;
                case tmx::Property::Type::Float:
                    propertyMap.emplace(propName, 
                        std::any_cast<float>(property.getFloatValue()));
                    break;
                case tmx::Property::Type::Int:
                    propertyMap.emplace(propName, 
                        std::any_cast<int>(property.getIntValue()));
                    break;
                case tmx::Property::Type::String:
                    propertyMap.emplace(propName,
                        std::any_cast<std::string>(property.getStringValue()));
                    break;
                case tmx::Property::Type::Colour:
                    propertyMap.emplace(propName,
                        std::any_cast<tmx::Colour>(property.getColourValue()));
                    break;
                case tmx::Property::Type::File:
                    propertyMap.emplace(propName, 
                        std::any_cast<std::string>(property.getFileValue()));
                    break;
                case tmx::Property::Type::Undef:
                    break;                    
            } 
        }
        tileProperties.emplace(tile.ID, propertyMap);
    }
}

// get the clip in this spritesheet for the given tile (as SDL_Rect wrapper Sprite obj.) 
std::shared_ptr<Sprite> SpriteSheet::getSprite(int tileID) const {
    return sprites.at(tileID);
}

int SpriteSheet::getFirstGID() const {
    return firstGID;
}

SDL_Texture * SpriteSheet::getTexture() const {
    return spritesheetTexture->getTexture().get();
}

int SpriteSheet::getNumSprites() const {
    return sprites.size();
}