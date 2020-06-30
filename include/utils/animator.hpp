// class for handling the playback of animations

#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "utils/animation.hpp"

class Animator {
    public:
        Animator();

        void start(bool reverse = false);

        void update(float delta);
        void render(int x, int y, SDL_Renderer * renderer, double angle = 0.0) const;

        void setAnimating(bool animating);
        bool isAnimating() const;

        float getMsFromStart() const;

        void setCurrAnimation(std::shared_ptr<Animation> currAnimation);

    private:
        // track the animation progress
        bool animating = false;
        bool reverse = false;

        int currFrame = 0;
        
        float msFromStart = 0;

        std::shared_ptr<Animation> currAnimation;

};

#endif // ANIMATOR_HPP