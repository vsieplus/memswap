/**
 * @file gamestate.cpp
 * @author vsie
 * @brief abstract class gamestate
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "memswap.hpp"
#include "gameStates/gamestate.hpp"

// create black rect filling the screen, and then gradually increase/decrease opacity
void GameState::fade(SDL_Renderer * renderer, MemSwap * game, bool in) const {
    Uint8 currOpacity = in ? 255 : 0;
    Uint8 stopOpacity = in ? 0 : 255;
    SDL_Rect screenArea = {0, 0, game->getScreenWidth(), game->getScreenHeight()};

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    while(currOpacity != stopOpacity) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // render the state in the bg
        render(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, currOpacity);
        SDL_RenderFillRect(renderer, &screenArea);

        SDL_RenderPresent(renderer);

        currOpacity = in ? currOpacity - 15 : currOpacity + 15;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}