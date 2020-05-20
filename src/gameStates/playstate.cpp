/**
 * @file playstate.cpp
 * @author vsie
 * @brief implementation for PlayState class
 * @version 0.1
 * @date 2020-05-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "gameStates/playstate.hpp"

PlayState::PlayState() {
    gameStateID = GAME_STATE_PLAY;
}

PlayState::~PlayState() {
    exitState();
}

void PlayState::enterState() {

}

void PlayState::exitState() {

}

void PlayState::handleEvents() {
    
}

void PlayState::update() {
    printf("play state");
}

/// Render function for the game state
void PlayState::render(SDL_Window * window, SDL_Renderer * renderer) {

}