// Header for Menu State

#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "gameStates/gamestate.hpp"

// Singleton class for the Menu State
class MenuState : public GameState {
    public:
        MenuState();

        ~MenuState();

        void enterState() override;
        void exitState() override;

        void update() override;
        void render(SDL_Window * window, SDL_Renderer * renderer) override;
};

#endif // MENUSTATE_HPP