// wrapper class for animation spritesheet

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "utils/spritesheet.hpp"

class Animation {
    public:
        Animation(std::string animationPath, SDL_Renderer * renderer, 
            int numFrames, int frameWidth, int frameHeight);

        void update(float delta);
        void render(int x, int y, SDL_Renderer * renderer);

        void setAnimating(bool animating);
        bool isAnimating() const;

    private:
        SpriteSheet animationSpritesheet;

        // track the animation progress
        bool animating = false;

        int numFrames;
        int currFrame = 0;

        // amt. of ms to show each frame of the animation for
        const static int MS_PER_FRAME = 250;

        // size of animation frames
        int frameWidth;
        int frameHeight;

        float msFromStart = 0;
        
};

#endif // ANIMATION_HPP