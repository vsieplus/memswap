// Header file for memswap.cpp

#ifndef MEMSWAP_HPP
#define MEMSWAP_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "gameStates/gamestate.hpp"

#include "utils/resmanager.hpp"

class MemSwap {
    private:
        // for time
        float delta = 0;        // ms passed since last call to update
        Uint64 lastTime = 0;
        Uint64 currTime;

        GameStateID nextState = GAME_STATE_NULL;
        GameStateID currState = GAME_STATE_NULL;

        // Window constants
        int screenWidth = 640;
        int screenHeight = 480;

        // Audio
        const int SOUND_FREQ = 44100;
        const int NUM_CHANNELS = 2;
        const int SAMPLE_SIZE = 2048;

        // player data/stats
        int playTime;               // in hours:minutes (time in play state)
        int levelsCompleted;        // level progress (out of 30)
        int perfectPlays;           // levels completed with no resets
        int tilesFlipped;           // total tiles flipped during play
        int timesReset;             // total level resets


        std::string playerName;

        const std::string GAME_TITLE = "ReverShade";
        const std::string RES_PATHS_FILE = "res/res_paths.json";
        const std::string ICON_ID = "window_icon";

        bool playing = true;

        bool minimized = false;
        bool fullscreen = false; // Press F11 to toggle fullscreen
        
        SDL_Window * window;
        SDL_Renderer * renderer;
        SDL_Event e;

        // outline color (for gui elements)
        SDL_Color outlineColor = {0x83, 0x86, 0xF5, 0xFF};

        // map for tracking the game states/the current state
        std::unordered_map<GameStateID, std::unique_ptr<GameState>> gameStates;

        // Resource manager for the game
        ResManager resourceManager;
        
        // initialize
        SDL_Renderer * init ();
        bool initLibs();

        // state management
        void changeState();
        void addGameState(GameStateID gameStateID, std::unique_ptr<GameState> & state);
        void removeGameState(GameStateID gameStateID);

    public:
        /// Constructor
        MemSwap();
        
        // (called during splash state)
        int loadNextResource();

        // Handle events
        void handleEvents();
        void handleWindowEvents();

        /// Update the game state
        void update();

        /// Render the current state of the game
        void render() const;

        // Manage game states
        void setNextState(GameStateID gameID);

        void quit();

        bool isPlaying() const;
        GameStateID getGameStateID() const;
        SDL_Event getEvent() const;
        SDL_Renderer * getRenderer() const;
        SDL_Color getOutlineColor() const;

        int getScreenWidth() const;
        int getScreenHeight() const;

        ResManager & getResManager();
};

#endif // MEMSWAP_HPP