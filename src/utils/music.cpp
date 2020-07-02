// implementation for music resource class

#include "utils/music.hpp"

Music::Music(std::string musicPath) : 
    music(Mix_LoadMUS(musicPath.c_str()), Mix_FreeMusic) {}

// play the track if not currently playing
void Music::play() {
    if(Mix_PlayingMusic() == 0) {
        // -1 for looping, 1000 ms fade-in
        Mix_FadeInMusic(music.get(), -1, 750); 
    } 
}

// cut volume in half (e.g. b/c of pause/popup)
void Music::deafen() {
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}

// set volume to default (max)
void Music::undeafen() {
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void Music::pause() {
    Mix_PauseMusic();
}

void Music::resume() {
    Mix_ResumeMusic();
}

void Music::stop() {
    Mix_FadeOutMusic(750);
}