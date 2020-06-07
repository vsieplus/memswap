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

#include "memswap.hpp"
#include "gameStates/splashstate.hpp"
#include "utils/resmanager.hpp"

SplashState::SplashState() : GameState(GAME_STATE_SPLASH) {}

void SplashState::enterState(MemSwap * game) {
    // load splash textures prematurely
    bgTexture.loadTexture(game->getResManager().getResPath(BG_ID), 
        game->getRenderer());

    // set advText render pos
    advTextX = (game->getScreenWidth() / 3);
    advTextY = (3 * game->getScreenHeight() / 5);
}

void SplashState::exitState() {

}

// Events to handle during splash screen
void SplashState::handleEvents(MemSwap * game, const Uint8 * keyStates) {
    // Check if user pressed Enter to advance from splash
    if(keyStates[SDL_SCANCODE_RETURN]) {
        advance = true;
    } 
}

void SplashState::update(MemSwap * game, float delta) {
    // Continue loading resources until finished
    if(loadingRes) {
        game->getResManager().loadNextResource();
        loadingRes = game->getResManager().loadingResources();
    } else {
        if (advance) {
            // Otherwise finish the SPLASH state and set next as the MENU state
            game->setNextState(GAME_STATE_PLAY);
        }

        // retrieve loaded font
        if(!splashFont.get()) {
            splashFont = game->getResManager().getFont(FONT_ID);
        }

        // start rendering advance text graphic to signal user
        if(!splashFont->isRendering()) {
            // typed and flashing, with dark green text
            splashFont->initRenderText(advTextX, advTextY, ADV_TEXT, true, true,
                0x65, 0xDC, 0x98);
        } else {
            splashFont->updateText(delta);
        }
    }     
}

/// Render function for the game state
void SplashState::render(SDL_Renderer * renderer) const {
    // Render background
    bgTexture.render(0, 0, renderer);

    // Render progress

    // Render graphic indicating loading is done
    if(!loadingRes) {
        if(splashFont.get() && splashFont->isRendering()) {
            splashFont->renderText(renderer);
        }
    }
}