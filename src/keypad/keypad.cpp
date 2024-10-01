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

void Keypad::handleKeydown(SDL_Event event){
    switch(event.key.keysym.sym){
        // 1 key to 1 keypad
        case SDLK_1: {
            current[1] = true;
            break;
        }
        // 2 key to 2 keypad
        case SDLK_2: {
            current[2] = true;
            break;
        }
        // 3 key to 3 keypad
        case SDLK_3: {
            current[3] = true;
            break;
        }
        // 4 key to C keypad
        case SDLK_4: {
            current[12] = true;
            break;
        }
        // Q key to 4 keypad
        case SDLK_q: {
            current[4] = true;
            break;
        }
        // W key to 5 keypad
        case SDLK_w: {
            current[5] = true;
            break;
        }
        // E key to 6 keypad
        case SDLK_e: {
            current[6] = true;
            break;
        }
        // R key to D keypad
        case SDLK_r: {
            current[13] = true;
            break;
        }
        // A key to 7 keypad
        case SDLK_a: {
            current[7] = true;
            break;
        }
        // S key to 8 keypad
        case SDLK_s: {
            current[8] = true;
            break;
        }
        // D key to 9 keypad
        case SDLK_d: {
            current[9] = true;
            break;
        }
        // F key to E keypad
        case SDLK_f: {
            current[14] = true;
            break;
        }
        // Z key to A keypad
        case SDLK_z: {
            current[10] = true;
            break;
        }
        // X key to 0 keypad
        case SDLK_x: {
            current[0] = true;
            break;
        }
        // C key to B keypad
        case SDLK_c: {
            current[11] = true;
            break;
        }
        // V key to F keypad
        case SDLK_v: {
            current[15] = true;
            break;
        }
    }
}

void Keypad::handleKeyup(SDL_Event event){
    switch(event.key.keysym.sym){
        // 1 key to 1 keypad
        case SDLK_1: {
            current[1] = false;
            break;
        }
        // 2 key to 2 keypad
        case SDLK_2: {
            current[2] = false;
            break;
        }
        // 3 key to 3 keypad
        case SDLK_3: {
            current[3] = false;
            break;
        }
        // 4 key to C keypad
        case SDLK_4: {
            current[12] = false;
            break;
        }
        // Q key to 4 keypad
        case SDLK_q: {
            current[4] = false;
            break;
        }
        // W key to 5 keypad
        case SDLK_w: {
            current[5] = false;
            break;
        }
        // E key to 6 keypad
        case SDLK_e: {
            current[6] = false;
            break;
        }
        // R key to D keypad
        case SDLK_r: {
            current[13] = false;
            break;
        }
        // A key to 7 keypad
        case SDLK_a: {
            current[7] = false;
            break;
        }
        // S key to 8 keypad
        case SDLK_s: {
            current[8] = false;
            break;
        }
        // D key to 9 keypad
        case SDLK_d: {
            current[9] = false;
            break;
        }
        // F key to E keypad
        case SDLK_f: {
            current[14] = false;
            break;
        }
        // Z key to A keypad
        case SDLK_z: {
            current[10] = false;
            break;
        }
        // X key to 0 keypad
        case SDLK_x: {
            current[0] = false;
            break;
        }
        // C key to B keypad
        case SDLK_c: {
            current[11] = false;
            break;
        }
        // V key to F keypad
        case SDLK_v: {
            current[15] = false;
            break;
        }
    }
}

bool Keypad::isPressed(uint8_t button){
    return current[button];
}

void Keypad::updatePrevious(){
    for(int i = 0; i < 0xF; i++){
        previous[i] = current[i];
    }
}

bool Keypad::beenPressed(uint8_t button){
    if(previous[button] != current[button]){
        return true;
    }

    return false;
}