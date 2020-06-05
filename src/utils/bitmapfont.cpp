// bitmap font class implementation

#include "utils/bitmapfont.hpp"

BitmapFont::BitmapFont(std::string texturePath, std::string configPath, 
    SDL_Renderer * renderer) {
    buildFont(texturePath, configPath, renderer);
}

// build the font - load the texture + define the character clips
bool BitmapFont::buildFont(std::string texturePath, std::string configPath,
    SDL_Renderer * renderer) {
    bitmapTexture.loadFromFile(texturePath, renderer);

    // process the config file
}

// initialize variables for typed or static text rendering
void BitmapFont::initRenderText(int x, int y, std::string text, bool typed) {
    rendering = true;
    renderX = x;
    renderY = y;
    currString = text;
    currChar = typed ? 0 : text.length() - 1;
}

// show text using the bitmap; Use 'typing animation' to render
void BitmapFont::renderText(SDL_Renderer * renderer) const {
    // render each char in the string up to currChar
    int x = renderX, y = renderY;

    for(int i = 0; i < currChar; i++) {
        // handle special chars.
        if(currString[i] == ' ') {
            // move over
            x += spaceChar;
        } else if(currString[i] == '\n' || x > 640 - H_PAD) {
            // move down and back
            y += newLineChar;
            x = renderX;
        } else {
            // access correct clip using ascii val.
            int ascii = (unsigned char) currString[i];

            bitmapTexture.render(x, y, renderer, &charClips.at(ascii));

            // glyph width + padding between chars
            x += charClips.at(ascii).w + 1;
        }
    }
}

// if already rendering text call these functions
void BitmapFont::updateText(float delta) {
    // check if already reached end of string
    if(currChar == currString.length() - 1) {
        return;
    }

    // update string progress/current character count based on time
    stringProgress += textSpeed * (delta/1000);

    currChar = (int) stringProgress;
    if(currChar > currString.length() - 1) {
        currChar = currString.length() - 1;
    }
}

bool BitmapFont::isRendering() const {
    return rendering;
}