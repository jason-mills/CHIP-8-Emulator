#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Beeper{
public:
    Beeper();
    ~Beeper();

    void play() const;
    void stop() const;

private:
    static constexpr std::string beepFile = "assets/100.wav";
    Mix_Chunk* beepSound;
    int beepChannel;
};
