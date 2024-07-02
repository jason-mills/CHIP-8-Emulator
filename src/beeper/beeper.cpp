#include "beeper.hpp"

Beeper::Beeper(){
    if(SDL_Init(SDL_INIT_AUDIO) < 0) throw "SDL could not initialize audio";

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) < 0) throw "SDL Mixer could not open audio";

    beepSound = Mix_LoadMUS(beepFile.c_str());
    if(beepSound == nullptr) throw (std::string)"Failed to load beep sound. SDL_mixer Error: " + Mix_GetError();

    Mix_PlayMusic(beepSound, -1);
    Mix_PausedMusic();
}

Beeper::~Beeper(){
    Mix_FreeMusic(beepSound);

    Mix_Quit();
}

void Beeper::play(){
    Mix_ResumeMusic();
}

void Beeper::stop(){
    Mix_PauseMusic();
}