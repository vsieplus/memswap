#include "utils/animator.hpp"

Animator::Animator() {}

void Animator::start(bool reverse) {
    this->reverse = reverse;

    msFromStart = 0;
    currFrame = reverse ? currAnimation->getNumFrames() - 1 : 0;
    if(!animating) setAnimating(true);
}

void Animator::update(float delta) {
    msFromStart += delta;
    
    if(reverse) {
        currFrame = currAnimation->getNumFrames() - 1
            - (msFromStart / currAnimation->getMsPerFrame());
    } else {
        currFrame = msFromStart / currAnimation->getMsPerFrame();
    }
/* 
    printf("current frame: %dout of %d\n", currFrame, currAnimation->getNumFrames());
    printf("delta: %.6f\n", delta);
    printf("ms from start %.6f\n", msFromStart); */

    // check if Animator has finished, stop unless looping
    if((!reverse && currFrame > currAnimation->getNumFrames() - 1) ||
       (reverse && currFrame == 0)) {
        start(reverse);
        if(!currAnimation->isLooping()) {
            setAnimating(false);
            currAnimation.reset();
        }
    }
}

void Animator::render(int x, int y, SDL_Renderer * renderer, double angle) const {
    currAnimation->render(x, y, currFrame, renderer, angle);
}

void Animator::setAnimating(bool animating) {
    this->animating = animating;
}

bool Animator::isAnimating() const {
    return animating;
}

float Animator::getMsFromStart() const {
    return msFromStart;
}

void Animator::setCurrAnimation(std::shared_ptr<Animation> currAnimation) {
    this->currAnimation = currAnimation;
}