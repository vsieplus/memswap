// Header for gamestate.cpp

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SDL.h>

enum GameStateID {
    GAME_STATE_MENU,
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_SCORE,
};

class GameState {
    protected:
        GameState(int gameStateID) : gameStateID(gameStateID) {}
        int gameStateID; 

    public:
        virtual ~GameState() {}

        /// Update method for the particular game state 
        virtual void update() = 0;

        /// Render function for the game state
        virtual void render(SDL_Window * window, SDL_Renderer * renderer) = 0;
};

#endif // GAMESTATE_HPP