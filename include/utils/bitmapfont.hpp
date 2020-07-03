// Header for class of bitmap font, for use with SDL

#ifndef BITMAPFONT_HPP
#define BITMAPFONT_HPP

#include <vector>
#include <map>
#include <string>

#include <SDL.h>

#include "utils/texture.hpp"

struct CharSpacing {
    int charXOffset;     // how much to offset when drawing a char
    int charYOffset;
    int charXAdvance;    // how much to advance after drawing a char
};

// class for a font bitmap spritesheet
class BitmapFont {
    private:
        // the bitmap texture
        Texture bitmapTexture;

        // the character clips; key: ascii value, val: SDL_Rect defining char. clip
        std::map<int, SDL_Rect> charClips;

        // character spacings
        std::map<int, CharSpacing> charSpacings;

        // spacing characters
        const char SPACE_CHAR = ' ';
        const char NEWLINE_CHAR = '\n';
        int spaceChar = 0;
        int newLineChar = 0;

        // (native) screen resolution
        int screenWidth,screenHeight;

        int H_PAD = 100;             // space between edge of window/text

        // variables for text rendering (w/'typing' animation)        
        int textSpeed = 24;          // # of chars to render per second
        unsigned int currChar = 0;   // current character of string we've reached

        int renderX = 0;
        int renderY = 0;

        float stringProgress = 0;           // how much of string has been typed (0-1)
        bool renderingDynamic = false;      // if currently rendering
        bool flashing = false;              // if text is flashing

        std::string currString;             // current (dynamic) strings to render

        // strings for parsing bmfont fnt->json file
        const std::string TEXTURE_LABEL = "pages";
        const std::string COMMON_DATA_LABEL = "common";
        const std::string CHARMAP_LABEL = "chars";

        const char PATH_SEP = '/';

        void updateAlpha();

        // build the font
        void buildFont(std::string configPath, SDL_Renderer* renderer);

    public:
        BitmapFont(std::string configPath, SDL_Renderer * renderer);

        // render text using the bitmap
        void initRenderDynamicText(int x, int y, const std::string & text, 
            bool typed, bool flashing = false);
        
        // dynamic/static text rendering
        void renderText(SDL_Renderer * renderer) const;
        void renderText(SDL_Renderer * renderer, const std::string & text, 
            int x, int y) const;
        void renderText(SDL_Renderer * renderer, const std::string & text, 
            int x, int y, unsigned int lastCharIdx) const;


        void updateText(float delta);
        void setFontColor(const SDL_Color & fontColor);
        void setAlpha(Uint8 a);
        void setRenderingDynamic(bool renderingDynamic);

        bool isRenderingDynamic() const;
        int getLineHeight() const;
        int getTextHeight(const std::string & text) const;
        int getTextWidth(const std::string & text) const;
};


#endif //BITMAPFONT_HPP