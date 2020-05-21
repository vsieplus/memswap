// Header file for main.cpp

#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdio.h>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Window constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string GAME_TITLE = "Memory Swap";

// Audio
const int SOUND_FREQ = 44100;
const int NUM_CHANNELS = 2;
const int SAMPLE_SIZE = 2048;

/// initialize SDL window and renderer
bool init(SDL_Window *& window, SDL_Renderer *& renderer);

/// initialize SDL libararies we're using
bool initLibs();

/// quit SDL components and free resources
void quit(SDL_Window *& window, SDL_Renderer *& renderer);

#endif // MAIN_HPP