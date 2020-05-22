/**
 * @file memswap.cpp
 * @author vsie
 * @brief implementation for game engine
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

 #include "memswap.hpp"

MemSwap::MemSwap() {
    // Initialize SDL components
    if(!(init() && initLibs())) {
        printf("Failed to initialize SDL");
    }

    // Start game in splash state to load res/
    setNextState(GAME_STATE_SPLASH);
    changeState();
}


/**
 * @brief initialize SDL window/renderer
 * 
 * @return true if successful
 * @return false if unsuccessful
 */
bool MemSwap::init () {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
		return false;
	} 

	// Try to create window
	window = SDL_CreateWindow(GAME_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		printf("SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}


/**
 * @brief initialize SDL libraries we're using
 * 
 * @return true if successful
 * @return false if unsuccessful
 */
bool MemSwap::initLibs() {
	// Initialize SDL_image
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_Image Error: %s\n", IMG_GetError());
		return false;
	}

	// Init SDL_ttf
	if(TTF_Init() == -1) {
		printf("SDL_ttf error: %s\n", TTF_GetError());
		return false;
	}

	// Initialize Mixer
	if(Mix_OpenAudio(SOUND_FREQ, MIX_DEFAULT_FORMAT, NUM_CHANNELS, 
		SAMPLE_SIZE) < 0) {
		printf("SDL_mixer error %s\n", Mix_GetError());
		return false;
	}

	return true;
}

/// Handle game events
void MemSwap::handleEvents() {
    gameStates.back()->handleEvents(this);
}


/// Update the current game state
void MemSwap::update() {
    gameStates.back()->update(this);

    changeState();
}

/// Render the current game state
void MemSwap::render() {
    gameStates.back()->render(window, renderer);
}

/// Set next state to change to indicated by the given state ID
void MemSwap::setNextState(int stateID) {
    nextState = stateID;
}

/// Change states if needed
void MemSwap::changeState() {
    int currState = getGameStateID();

    if(nextState != currState) {
        // If next state set to exit, stop playing
        if(nextState == GAME_STATE_EXIT) {
            playing = false;
            return;
        }

        // Pop off current state, unless it's a PLAY state
        if(currState != GAME_STATE_NULL && currState != GAME_STATE_PLAY) {
            popGameState();
        }

        std::unique_ptr<GameState> nextGameState = NULL;

        switch(nextState) {
            case GAME_STATE_SPLASH:
                // Load game resources from splash state
                nextGameState = std::make_unique<SplashState>();
                break;
            case GAME_STATE_MENU:

                break;
            case GAME_STATE_PLAY:

                break;
            case GAME_STATE_SCORE:

                break;
        }

        // Push the next game state
        pushGameState(nextGameState);
    }
}

/// Add a game state to the stack (enter a game state)
void MemSwap::pushGameState(std::unique_ptr<GameState> & state) {
    state->enterState();
    gameStates.push_back(std::move(state));
}

/// Remove a game state from the stack (exit a game state)
void MemSwap::popGameState() {
    gameStates.pop_back();
}

void MemSwap::quit() {
    gameStates.clear();

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool MemSwap::isPlaying() { 
    return playing; 
}

int MemSwap::getGameStateID() { 
    if(gameStates.empty()) {
        return GAME_STATE_NULL;
    }

    return gameStates.back()->getGameStateID(); 
}