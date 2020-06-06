// Header for Score State

#ifndef SCORESTATE_HPP
#define SCORESTATE_HPP

#include <memory>

#include "gameStates/gamestate.hpp"
#include "utils/bitmapfont.hpp"

// Class for the Score State
class ScoreState : public GameState {
    private:
        std::shared_ptr<BitmapFont> font;

        const std::string FONT_ID = "mainFont";

    public:
        ScoreState(MemSwap * game);

        void enterState(MemSwap * game) override;
        void exitState() override;

        void handleEvents(MemSwap * game, const Uint8 * keyStates) override;
        void update(MemSwap * game, float delta) override;
        void render(SDL_Renderer * renderer) const override;
};

#endif // SCORESTATE_HPP