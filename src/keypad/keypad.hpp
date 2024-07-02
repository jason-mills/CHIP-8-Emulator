#pragma once

#include <SDL2/SDL_events.h>

class Keypad{
public:
    void handleKeypress(SDL_Event event, bool pressed);
    void handleKeyup(SDL_Event event);

    bool isPressed(uint8_t button);
    bool beenPressed(uint8_t button);

private:
    bool buttons[16] = {false}, pressed[16] = {false};
};
