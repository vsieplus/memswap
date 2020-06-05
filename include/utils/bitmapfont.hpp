// Header for class of bitmap font, for use with SDL

#ifndef BITMAPFONT_HPP
#define BITMAPFONT_HPP

#include <map>
#include <string>

#include <SDL.h>

#include "utils/texture.hpp"

// class for a font bitmap spritesheet
class BitmapFont {
    private:
        // the bitmap texture
        Texture bitmapTexture;

        // the character clips; key: ascii value, val: SDL_Rect defining char. clip
        std::map<int, SDL_Rect> charClips;

        // spacing characters
        int newLineChar = 0;
        int spaceChar = 0;

        int H_PAD = 50;             // space between edge of window/text

        // for text rendering (w/'typing' animation)        
        int textSpeed = 4;           // # of chars to render per second
        unsigned int currChar = 0;   // current character of string we've reached

        int renderX = 0;
        int renderY = 0;

        float stringProgress = 0;   // how much of string has been typed (0-1)
        bool rendering = false;     // if currently rendering

        std::string currString;     // current string to render


    public:
        BitmapFont(std::string texturePath, std::string configPath, SDL_Renderer * renderer);

        // build the font
        void buildFont(std::string texturePath, std::string configPath, SDL_Renderer* renderer);

        // render text using the bitmap
        void initRenderText(int x, int y, std::string text, bool typed);
        void renderText(SDL_Renderer * renderer) const;

        void updateText(float delta);

        bool isRendering() const;
};


#endif //BITMAPFONT_HPP