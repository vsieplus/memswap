#ifndef TILE_HPP
#define TILE_HPP

#include <SDL.h>

#include "utils/sprite.hpp"

class Level;

enum TileParity {
    PARITY_NONE,    // 0 ~ none
    PARITY_GRAY,    // 1 ~ gray
    PARITY_PURPLE   // 2 ~ purple
};

class Tile {
    private:
        // indicate tile color (1:gray, 2:purple) | (-1 for no parity)                            
        int tileParity;
        
        // the tile's sprite
        std::shared_ptr<Sprite> tileSprite;

        bool flipped = false;

        SDL_Rect renderArea;     // where on screen to render
        
    public:
        Tile(int mapX, int mapY, int tileWidth, int tileHeight, int tileParity,
            std::shared_ptr<Sprite> tileSprite);

        void update(Level * level);

        void render(SDL_Renderer * renderer) const;

        // flip the tile parity
        void flip(std::shared_ptr<Sprite> newTileSprite);
        
        int getTileParity() const;

        bool isFlipped() const;
};

#endif