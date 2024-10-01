#include "beeper.hpp"

Beeper::Beeper(){
    if(SDL_Init(SDL_INIT_AUDIO) < 0) throw "SDL could not initialize audio";

    if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 1, 2048) < 0) throw "SDL Mixer could not open audio";

    beepSound = Mix_LoadWAV(beepFile.c_str());
    if(beepSound == nullptr) throw (std::string)"Failed to load beep sound. SDL_mixer Error: " + Mix_GetError();

    beepChannel = Mix_PlayChannel(-1, beepSound, -1);
    Mix_Pause(-1);
}

Beeper::~Beeper(){
    Mix_FreeChunk(beepSound);
    Mix_Quit();
}

void Beeper::play() const{
    Mix_Resume(beepChannel);
}

void Beeper::stop() const{
    Mix_Pause(beepChannel);
}