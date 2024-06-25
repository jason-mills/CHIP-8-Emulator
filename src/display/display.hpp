#pragma once

#include "keypad.hpp"

#include <SDL2/SDL.h>

class Display{
public:
    Display(Keypad* aKeypad, int width = 0);
    ~Display();

    void processEvents();
    void update();

    void clear();
    bool loadSprite(int8_t x, uint8_t y, uint8_t sprite[], uint8_t length);

    bool isRunning();
    
private:
    const char windowName[sizeof("CHIP 8 Emulator")] = "CHIP 8 Emulator";
    const int defaultWidth = 640;
    const int defaultHeight = 320;

    Keypad* keypad;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    bool pixels[32][64] = {};

    bool running = true;
};
