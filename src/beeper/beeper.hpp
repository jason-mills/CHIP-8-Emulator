#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Beeper{
public:
    Beeper();
    ~Beeper();

    void play();
    void stop();

private:
    const std::string beepFile = "assets/100.wav";
    Mix_Music* beepSound;
};
