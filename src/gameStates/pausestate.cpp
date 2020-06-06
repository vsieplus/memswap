/**
 * @file pausestate.cpp
 * @author vsie
 * @brief implementation for PauseState class
 * @version 0.1
 * @date 2020-05-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "gameStates/pausestate.hpp"

PauseState::PauseState() : GameState(GAME_STATE_PAUSE) {}


void PauseState::enterState(MemSwap * game) {

}

void PauseState::exitState() {

}

void PauseState::handleEvents(MemSwap * game, const Uint8 * keyStates) {
    
}

void PauseState::update(MemSwap * game, float delta) {
}

/// Render function for the game state
void PauseState::render(SDL_Renderer * renderer) const {

}