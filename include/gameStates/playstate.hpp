// Header for Play State

#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameStates/gamestate.hpp"

// Singleton class for the Play State
class PlayState : public GameState {
    public:
        PlayState();

        ~PlayState();

        void enterState() override;
        void exitState() override;

        void handleEvents() override;
        void update() override;
        void render(SDL_Window * window, SDL_Renderer * renderer) override;

        void pause();
};

#endif // PLAYSTATE_HPP