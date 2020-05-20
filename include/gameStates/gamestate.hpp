// Header for gamestate.cpp

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

#include <SDL.h>

enum GameStateID {
    GAME_STATE_SPLASH,  // load res
    GAME_STATE_MENU,    // menu
    GAME_STATE_PLAY,    // play state
    GAME_STATE_PAUSE,   // pause state
    GAME_STATE_SCORE,   // post-game/score state
};

class MemSwap;

class GameState {
    protected:
        int gameStateID; 

    public:
        // Entering/exiting this specific state
        virtual void enterState() = 0;
        virtual void exitState() = 0;

        // Changing to another state from this state
        void enterNewState(MemSwap * game, std::unique_ptr<GameState> & state);

        virtual ~GameState() {};

        /// Event handling method for the game state
        virtual void handleEvents() = 0;

        /// Update method for the particular game state 
        virtual void update() = 0;

        /// Render function for the game state
        virtual void render(SDL_Window * window, SDL_Renderer * renderer) = 0;

        int getGameStateID() {
            return gameStateID;
        }
};



#endif // GAMESTATE_HPP