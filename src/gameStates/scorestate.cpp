/**
 * @file scorestate.cpp
 * @author vsie
 * @brief implementation for ScoreState class
 * @version 0.1
 * @date 2020-05-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "gameStates/scorestate.hpp"

ScoreState::ScoreState(MemSwap * game) : GameState(GAME_STATE_SCORE) {
    font = game->getResManager().getFont(FONT_ID)
}

void ScoreState::enterState(MemSwap * game) {
    font->initRenderText(50, 50, "hello world, my name is bob.", true);
}

void ScoreState::exitState() {

}

void ScoreState::handleEvents(MemSwap * game, const Uint8 * keyStates) {
    
}

void ScoreState::update(MemSwap * game) {
    if(font->isRendering()) {
//        font.updateText(delta);
    }
}

/// Render function for the game state
void ScoreState::render(SDL_Renderer * renderer) const {
    if(font->isRendering()) {
        font->renderText(renderer);
    }
}