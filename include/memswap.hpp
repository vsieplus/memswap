// Header file for memswap.cpp

#ifndef MEMSWAP_HPP
#define MEMSWAP_HPP

#include <SDL.h>

#include "gameStates/gamestate.hpp"
#include "timer.hpp"

class MemSwap {
    private:
        SDL_Window * window;
        SDL_Renderer * renderer;

        Timer * timer;

        // For tracking the current and play state
        GameState * currState;

        bool playing = true;
        int gameStateID = GAME_STATE_MENU;

    public:
        /// Constructor
        MemSwap(SDL_Window * window, SDL_Renderer * renderer) : window(window),
            renderer(renderer) {}

        /// Update the game state
        void update();

        /// Render the current state of the game
        void render();

        /// Switch between game states
        void enterState(int gameStateID);

        bool isPlaying();
        int getGameStateID();
};

#endif // MEMSWAP_HPP