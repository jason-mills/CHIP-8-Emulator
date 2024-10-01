#include "keypad.hpp"

// the COSMAC VIP/HP48 keypad design is the usual implementation and will be used here
// the keypad is layed out as follows
// 123C
// 456D
// 789E
// A0BF

// on the keyboard we use the follwing "keypad"
// 1234
// QWER
// ASDF
// ZXCV

void Keypad::handleKeypress(SDL_Event event, bool pressed){
    switch(event.key.keysym.sym){
        // 1 key to 1 keypad
        case SDLK_1: {
            buttons[1] = pressed;
            break;
        }
        // 2 key to 2 keypad
        case SDLK_2: {
            buttons[2] = pressed;
            break;
        }
        // 3 key to 3 keypad
        case SDLK_3: {
            buttons[3] = pressed;
            break;
        }
        // 4 key to C keypad
        case SDLK_4: {
            buttons[12] = pressed;
            break;
        }
        // Q key to 4 keypad
        case SDLK_q: {
            buttons[4] = pressed;
            break;
        }
        // W key to 5 keypad
        case SDLK_w: {
            buttons[5] = pressed;
            break;
        }
        // E key to 6 keypad
        case SDLK_e: {
            buttons[6] = pressed;
            break;
        }
        // R key to D keypad
        case SDLK_r: {
            buttons[13] = pressed;
            break;
        }
        // A key to 7 keypad
        case SDLK_a: {
            buttons[7] = pressed;
            break;
        }
        // S key to 8 keypad
        case SDLK_s: {
            buttons[8] = pressed;
            break;
        }
        // D key to 9 keypad
        case SDLK_d: {
            buttons[9] = pressed;
            break;
        }
        // F key to E keypad
        case SDLK_f: {
            buttons[14] = pressed;
            break;
        }
        // Z key to A keypad
        case SDLK_z: {
            buttons[10] = pressed;
            break;
        }
        // X key to 0 keypad
        case SDLK_x: {
            buttons[0] = pressed;
            break;
        }
        // C key to B keypad
        case SDLK_c: {
            buttons[11] = pressed;
            break;
        }
        // V key to F keypad
        case SDLK_v: {
            buttons[15] = pressed;
            break;
        }
    }
}

void Keypad::handleKeyup(SDL_Event event){
    switch(event.key.keysym.sym){
        // 1 key to 1 keypad
        case SDLK_1: {
            pressed[1] = true;
            break;
        }
        // 2 key to 2 keypad
        case SDLK_2: {
            pressed[2] = true;
            break;
        }
        // 3 key to 3 keypad
        case SDLK_3: {
            pressed[3] = true;
            break;
        }
        // 4 key to C keypad
        case SDLK_4: {
            pressed[12] = true;
            break;
        }
        // Q key to 4 keypad
        case SDLK_q: {
            pressed[4] = true;
            break;
        }
        // W key to 5 keypad
        case SDLK_w: {
            pressed[5] = true;
            break;
        }
        // E key to 6 keypad
        case SDLK_e: {
            pressed[6] = true;
            break;
        }
        // R key to D keypad
        case SDLK_r: {
            pressed[13] = true;
            break;
        }
        // A key to 7 keypad
        case SDLK_a: {
            pressed[7] = true;
            break;
        }
        // S key to 8 keypad
        case SDLK_s: {
            pressed[8] = true;
            break;
        }
        // D key to 9 keypad
        case SDLK_d: {
            pressed[9] = true;
            break;
        }
        // F key to E keypad
        case SDLK_f: {
            pressed[14] = true;
            break;
        }
        // Z key to A keypad
        case SDLK_z: {
            pressed[10] = true;
            break;
        }
        // X key to 0 keypad
        case SDLK_x: {
            pressed[0] = true;
            break;
        }
        // C key to B keypad
        case SDLK_c: {
            pressed[11] = true;
            break;
        }
        // V key to F keypad
        case SDLK_v: {
            pressed[15] = true;
            break;
        }
    }
}

bool Keypad::isPressed(uint8_t button) const{
    return buttons[button];
}

bool Keypad::beenPressed(uint8_t button){
    if(pressed[button]){
        pressed[button] = false;
        return true;
    }

    return false;
}