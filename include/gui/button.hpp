// class for button gui element

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>
#include <SDL.h>

#include "utils/texture.hpp"
#include "utils/bitmapfont.hpp"

class Button {
    public:
        // constructor for a plain button
        Button(int screenX, int screenY, bool clickable,
            std::shared_ptr<Texture> buttonSprite, SDL_Color outlineColor);

        // constructor for a button to contain text inside
        Button(int screenX, int screenY, bool clickable, 
            std::shared_ptr<Texture> buttonSprite, SDL_Color outlineColor,
            std::string label, std::shared_ptr<BitmapFont> labelFont);

        // mouse or keyboard events (depending on GUI type)
        void handleEvents(const SDL_Event & e);
        void handleMouseEvents(const SDL_Event & e);
        void handleKeyEvents(const SDL_Event & e);

        void update();
        void render(SDL_Renderer * renderer) const;

        void setFocus(bool focus);

        bool isActivated() const;
        void setActivated(bool activated);

    private:
        std::shared_ptr<Texture> buttonSprite;

        // if the button contains a custom label store it here
        std::string buttonLabel;

        // the font to use to render the label
        std::shared_ptr<BitmapFont> buttonFont;

        // button outline
        SDL_Rect buttonOutline;

        // outline color
        SDL_Color outlineColor;

        // position on screen
        int screenX, screenY;

        // position of text
        int labelX, labelY;

        // amt to shift r/g by for flashing effect
        int colorShiftMax;
        int currShift = 0;
        const int COLOR_SHIFT_AMT = 2;

        bool darkening = true;

        // if button is part of clickable gui (or gamepad controlled focus)
        bool clickable;

        // if the button has gui focus
        bool inFocus = false;

        // whether the mouse is over/on the button + down or not
        bool mouseOn = false;
        bool mouseDown = false;

        // use this to determine when to take action
        bool activated = false;

        bool hasLabel;

        int initLabelX();
        int initLabelY();
};

#endif // BUTTON_HPP