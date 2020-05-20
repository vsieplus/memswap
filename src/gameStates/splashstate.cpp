/**
 * @file splashstate.cpp
 * @author vsie
 * @brief implementation for SplashState class - for loading game resources
 * @version 0.1
 * @date 2020-05-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "gameStates/splashstate.hpp"

SplashState::SplashState() {
    gameStateID = GAME_STATE_SPLASH;
}

SplashState::~SplashState() {
    exitState();
}

void SplashState::enterState() {

}

void SplashState::exitState() {

}

void SplashState::handleEvents() {
    
}

void SplashState::update() {

    
}

/// Render function for the game state
void SplashState::render(SDL_Window * window, SDL_Renderer * renderer) {

}

void SplashState::loadResources() {

}