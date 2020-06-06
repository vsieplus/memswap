// Header file for Texture Texture wrapper class
 
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>
#include <string>
#include <exception>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture {
    private:
        // pointer to the SDL texture
        std::shared_ptr<SDL_Texture> texture;

        int width = 0;
        int height = 0;

        // width in bytes (4 bytes per pixel)
        int pitch = 0;
        const static int BYTES_PER_PIXEL = 4;

        // for texture transparency
        Uint8 textureAlpha = 255;
        const static int ALPHA_MAX = 255;
        const static int ALPHA_STEP = 5;

        bool alphaIncreasing = false;

        // for pixel access (e.g. for bitmap textures)
        void * texturePixels;

    public:
        Texture();

        // initializing texture from an image path
        void loadTexture(std::string path, SDL_Renderer * renderer);

        // load a bitmap texture
        void loadBitmapTexture(std::string path, SDL_Renderer * renderer);

        // set texture color
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        // blending
        void setBlendMode(SDL_BlendMode blending);

        // transparency
        void updateAlpha();             // flashing effect
        void setAlpha(Uint8 alpha);     // one-time update

        // pixel access/manip.
        bool lockTexture();
        bool unlockTexture();
        void * getPixels();
        int getPitch();
        Uint32 getPixel32(unsigned int x, unsigned int y);

        /**
         * @brief   Render the texture at position x,y to the given renderer
         * If provided, renders a specific clip of the texture, rotated at a 
         * particular angle/flipped
         */
        void render(int x, int y, SDL_Renderer* renderer, const SDL_Rect* clip = NULL,
            double angle = 0.0, SDL_Point* center = NULL,
            SDL_RendererFlip flip = SDL_FLIP_NONE) const;

        int getHeight();
        int getWidth();
        std::shared_ptr<SDL_Texture> getTexture() const;
};

#endif // TEXTURE_HPP