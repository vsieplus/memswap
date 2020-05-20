// Header for gamestate.cpp

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

#include <SDL.h>

enum GameStateID {
    GAME_STATE_MENU,
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_SCORE,
};

class GameState {
    protected:
        int gameStateID; 

    public:
        virtual void enterState() = 0;
        virtual void exitState() = 0;

        virtual ~GameState() {};

        /// Update method for the particular game state 
        virtual void update() = 0;

        /// Render function for the game state
        virtual void render(SDL_Window * window, SDL_Renderer * renderer) = 0;

        int getGameStateID() {
            return gameStateID;
        }
};



#endif // GAMESTATE_HPP