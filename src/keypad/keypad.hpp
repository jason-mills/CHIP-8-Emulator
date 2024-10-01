#pragma once

#include <SDL2/SDL_events.h>

class Keypad{
public:
    void handleKeydown(SDL_Event event);
    void handleKeyup(SDL_Event event);
    void updatePrevious();

    bool isPressed(uint8_t button);
    bool beenPressed(uint8_t button);

private:
    bool previous[16] = {false}, current[16] = {false};
    // bool buttons[16] = {false}, pressed[16] = {false};
};
