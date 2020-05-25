/**
 * @file main.cpp
 * @author vsie
 * @brief driver class for Memory Swap
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "main.hpp"
#include "memswap.hpp"

int main(int argc, char* args[]) {
	MemSwap memSwap;

	// Game Loop
	while(memSwap.isPlaying()) {
		memSwap.handleEvents();
		memSwap.update();
		memSwap.render();		
	}

	memSwap.quit();

    return 0;
}