#include "gui/label.hpp"

Label::Label(int screenX, int screenY, std::shared_ptr<Texture> labelSprite) :
    Label(screenX, screenY, labelSprite, "", nullptr, (SDL_Color) {0, 0, 0, 0}){}

Label::Label(int screenX, int screenY, std::shared_ptr<Texture> labelSprite,
    std::string labelText, std::shared_ptr<BitmapFont> labelFont, SDL_Color textColor) : 
    labelSprite(labelSprite), labelText(labelText), labelFont(labelFont), 
    textColor(textColor),
    screenX(screenX), screenY(screenY),
    textX(initTextX()),
    textY(initTextY()),
    hasText(labelFont != nullptr) {}

int Label::initTextX() const {
    int x = 0;

    if(labelFont.get() && !labelText.empty()) {
        x = screenX + labelSprite->getWidth() / 2 - 
            labelFont->getTextWidth(labelText) / 2;
    }

    return x;
}

int Label::initTextY() const {
    int y = 0;

    if(labelFont.get() && !labelText.empty()) {
        y = screenY + labelSprite->getHeight() / 2 - 
            labelFont->getLineHeight() / 2;
    }

    return y;
}

void Label::render(SDL_Renderer * renderer) const {
    labelSprite->render(screenX, screenY, renderer);

    if(hasText) {
        labelFont->setFontColor(textColor);
        labelFont->renderText(renderer, labelText, textX, textY);
    }
}