#include "display.hpp"

Display::Display(Keypad& aKeypad, int width) : keypad(aKeypad) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) throw "SDL could not initialize video";

    if(width == -1){
        window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, defaultWidth, defaultHeight, SDL_WINDOW_MAXIMIZED);
        if(window == nullptr) throw "SDL could not create window";
    }
    else if(width == 0){
        window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, defaultWidth, defaultHeight, SDL_WINDOW_RESIZABLE);
        if(window == nullptr) throw "SDL could not create window";
    }
    else{
        int height = width / 2;
        window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if(window == nullptr) throw "SDL could not create window";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) throw "SDL could not create renderer";
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 32);
    if(texture == nullptr) throw "SDL could not create texture";

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}

Display::~Display(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);

    renderer = nullptr;
    window = nullptr;
    texture = nullptr;

    SDL_Quit();
}

void Display::processEvents(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:{
                running = false;
                break;
            }
            case SDL_KEYDOWN:{
                keypad.handleKeypress(event, true);
                break;
            }
            case SDL_KEYUP:{
                keypad.handleKeypress(event, false);
                keypad.handleKeyup(event);
                break;
            }
        }
    }
}

void Display::update(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Display::isRunning(){
    return running;
}

void Display::clear(){
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64; j++){
            pixels[i][j] = false;
        }
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}

bool Display::loadSprite(int8_t x, uint8_t y, uint8_t sprite[], uint8_t length){
    bool pixelOverwritten = false;

    uint8_t bitmask;
    int xReset = x;

    SDL_SetRenderTarget(renderer, texture);

    for(uint8_t i = 0; i < length; i++){
        bitmask = 0x80;

        for(int j = 0; j < 8; j++){
            if(bitmask & sprite[i]){
                if(pixels[y][x]){
                    pixelOverwritten = true;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, x, y);

                    pixels[y][x] = false;
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, x, y);
                    pixels[y][x] = true;
                }
                
            }
            x++;
            bitmask >>= 1;

            if(x > 63) break; // stop drawing if we are going off screen
        }

        x = xReset;
        y++;

        if(y > 31) break; // stop drawing if we are going off screen
    }

    SDL_SetRenderTarget(renderer, nullptr);

    return pixelOverwritten;
}
