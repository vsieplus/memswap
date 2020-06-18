// Label gui element

#ifndef LABEL_HPP
#define LABEL_HPP

#include "utils/texture.hpp"
#include "utils/bitmapfont.hpp"

class Label {
    public:
        // without text
        Label(int screenX, int screenY, std::shared_ptr<Texture> labelSprite);

        // with text
        Label(int screenX, int screenY, std::shared_ptr<Texture> labelSprite,
            std::shared_ptr<BitmapFont> labelFont, std::string label, 
            SDL_Color textColor);

        void render(SDL_Renderer * renderer) const;

        std::string getText() const;
        int getScreenX() const;
        int getScreenY() const;

    protected:
        std::shared_ptr<Texture> labelSprite;
        std::string labelText;
        std::shared_ptr<BitmapFont> labelFont;

        SDL_Color textColor;

        // coords of the texture
        int screenX, screenY;

        // coords of the label
        int textX, textY;

        bool hasText;

        int initTextX() const;
        int initTextY() const;
};

#endif //LABEL_HPP