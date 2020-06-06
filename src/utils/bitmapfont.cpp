// bitmap font class implementation

#include <fstream>
#include <nlohmann/json.hpp>
#include "utils/bitmapfont.hpp"

using json = nlohmann::json;

BitmapFont::BitmapFont(std::string configPath, SDL_Renderer * renderer) {
    buildFont(configPath, renderer);
}

// build the font - load the texture + define the character clips
void BitmapFont::buildFont(std::string configPath, SDL_Renderer * renderer) {
    json configJSON;
    std::ifstream instream(configPath);
    instream >> configJSON;

    std::map<std::string, json> configMap = configJSON;

    // load the texture
    auto texturePaths = configMap[TEXTURE_LABEL].get<std::vector<json>>();

    // get path to config file directory
    std::size_t lastSepIdx = configPath.find_last_of(PATH_SEP);

    auto texturePath = configPath.substr(0, lastSepIdx + 1) +
        texturePaths.back().get<std::string>();
    bitmapTexture.loadBitmapTexture(texturePath, renderer);

    // retrieve common data
    auto commonData = configMap[COMMON_DATA_LABEL].get<std::map<std::string, json>>();
    
    newLineChar = commonData["lineHeight"].get<int>();
    
    // loop through each char in the bitmap, retrieve clips/spacings
    auto charMaps = configJSON[CHARMAP_LABEL].get<std::vector<std::map<std::string, int>>>();
    for(auto & charMap: charMaps) {
        charClips.emplace(charMap["id"], (struct SDL_Rect) {charMap["x"],
            charMap["y"], charMap["width"], charMap["height"]});

        charSpacings.emplace(charMap["id"], (struct CharSpacing)
            {charMap["xoffset"], charMap["yoffset"], charMap["xadvance"]});
    }
}

// initialize variables for typed or static text rendering
void BitmapFont::initRenderText(int x, int y, std::string text, bool typed,
    bool flashing, Uint8 r, Uint8 g, Uint8 b) {
    rendering = true;
    renderX = x;
    renderY = y;
    currString = text;
    currChar = typed ? 0 : text.length() - 1;

    this->flashing = flashing;
    bitmapTexture.setColor(r, g, b);
}

// show text using the bitmap; Use 'typing animation' to render
void BitmapFont::renderText(SDL_Renderer * renderer) const {
    // render each char in the string up to currChar
    int x = renderX, y = renderY;

    for(unsigned int i = 0; i <= currChar; i++) {
        // check if space char
        if(currString[i] == SPACE_CHAR) {
            x += spaceChar;
        }

        // access correct clip using ascii val.
        int ascii = (unsigned char) currString[i];

        x += charSpacings.at(ascii).charXOffset;
        y += charSpacings.at(ascii).charYOffset;

        // handle new lines
        if(x > 640 - H_PAD) {
            // move down and back
            y += newLineChar;
            x = renderX;
        }

        bitmapTexture.render(x, y + charSpacings.at(ascii).charYOffset,
            renderer, &charClips.at(ascii));

        // add padding between chars
        x += charSpacings.at(ascii).charXAdvance;
    }
}

// if already rendering text call these functions
void BitmapFont::updateText(float delta) {
    // check if already reached end of string - update alpha
    if(currChar == currString.length() - 1) {
        if(flashing) updateAlpha();
        
        return;
    }

    // update string progress/current character count based on time
    stringProgress += textSpeed * (delta/1000);

    currChar = (int) stringProgress;
    if(currChar > currString.length() - 1) {
        currChar = currString.length() - 1;
    }
}

void BitmapFont::updateAlpha() {
    bitmapTexture.updateAlpha();
}

bool BitmapFont::isRendering() const {
    return rendering;
}