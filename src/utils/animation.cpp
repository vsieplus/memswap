#include "utils/animation.hpp"

Animation::Animation(std::string animationPath, SDL_Renderer * renderer, 
    int numFrames, int frameWidth, int frameHeight) : 
    animationSpritesheet(animationPath, renderer, frameWidth, frameHeight),
    numFrames(numFrames), frameWidth(frameWidth), frameHeight(frameHeight) {}

void Animation::update(float delta) {
    msFromStart += delta;
    currFrame = msFromStart / MS_PER_FRAME;

    // check if animation has finished
    if(currFrame > numFrames - 1) {
        animating = false;
        currFrame = 0;
        msFromStart = 0;
    }
}

void Animation::render(int x, int y, SDL_Renderer * renderer) {
    animationSpritesheet.getSprite(currFrame)->render(renderer, 
        (struct SDL_Rect) {x, y, frameWidth, frameHeight});
}

void Animation::setAnimating(bool animating) {
    this->animating = animating;
}

bool Animation::isAnimating() const {
    return animating;
}