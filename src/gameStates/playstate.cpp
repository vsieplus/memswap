// implementation for Play state

#include "memswap.hpp"
#include "gameStates/playstate.hpp"

PlayState::PlayState(std::string levelPath, MemSwap * game) : 
    GameState(GAME_STATE_PLAY), level(levelPath, game->getRenderer(), game) {}

void PlayState::enterState(MemSwap * game) {
    // retrieve bg texture
    bgTexture = game->getResManager().getTexture(BG_ID);
}

void PlayState::exitState() {

}

void PlayState::handleEvents(MemSwap * game, const Uint8 * keyStates) {
    // Check for level reset
    if(keyStates[SDL_SCANCODE_SPACE]) {
        // level.reset();
    }

    level.handleEvents(keyStates);
}

void PlayState::update(MemSwap * game) {
    level.update();
}

/// Render function for the game state
void PlayState::render(SDL_Renderer * renderer) const {
    // Render background
    bgTexture->render(0, 0, renderer);

    level.render(renderer);
}