#pragma once

#include <SDL2/SDL_events.h>

class Keypad{
public:
    void handleKeypress(SDL_Event event, bool pressed);
    bool isPressed(uint8_t button);

private:
    bool buttons[16] = {false};
};
