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

 #include "gameStates/gamestate.hpp"
 #include "memswap.hpp"

void GameState::enterNewState(MemSwap * game, std::unique_ptr<GameState> & state) {
    game->pushGameState(state);
}