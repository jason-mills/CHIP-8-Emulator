#include "keypad.hpp"

void Keypad::handleKeypress(SDL_Event event, bool pressed){
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

bool Keypad::isPressed(uint8_t button){
    return buttons[button];
}