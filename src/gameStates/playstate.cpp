// implementation for Play state

#include "memswap.hpp"
#include "gameStates/menustate.hpp"
#include "gameStates/playstate.hpp"

PlayState::PlayState() : GameState(GAME_STATE_PLAY) {}

void PlayState::enterState(MemSwap * game) {
    // retrieve bg texture
    bgTexture = game->getResManager().getTexture(BG_ID);

    // load current level (if entering from non-paused state)
    if(!game->isPaused()) {
        std::string levelPath = game->getResManager().getResPath(game->getCurrLevelID()); 
        level = Level(levelPath, game->getRenderer(), game);
    } else {
        game->setPaused(false);
    }
}

void PlayState::exitState() {

}

void PlayState::handleEvents(MemSwap * game, const SDL_Event & e) {
    const Uint8 * keyStates = SDL_GetKeyboardState(NULL);
    // Handle user selecting advance option after completing a level
    if(level.isCompleted()) {

    } else {
        // Check for level reset
        if(keyStates[SDL_SCANCODE_SPACE]) {
            //enterState(game);
            // level.reset();
        } else if(keyStates[SDL_SCANCODE_ESCAPE]) {
            // Check for pause
            game->setPaused(true);
        }

        level.handleEvents(keyStates);
    }
}

void PlayState::update(MemSwap * game, float delta) {
    if(game->isPaused()) {
        game->setNextState(GAME_STATE_PAUSE);
    } else {
        level.update(delta);

        // check if level is succesfully completed
        levelComplete = level.isCompleted();
        if(levelComplete) {
            // prepare to display msg to user

            // check if player ready to advance to next level or return to menu
            if(advanceLevel) {
                // 
            } else if (goToMenu) {
                game->setNextState(GAME_STATE_MENU);
                game->setCurrMenuScreen(MenuState::MenuScreen::MENU_LVLS);
            }
        }
    }
}

/// Render function for the game state
void PlayState::render(SDL_Renderer * renderer) const {
    // Render background
    bgTexture->render(0, 0, renderer);

    level.render(renderer);

    // render msg over level if level is completed
    if(levelComplete) {

    }
}