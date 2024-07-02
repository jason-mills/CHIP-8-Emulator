#pragma once

#include "fonts.hpp"
#include "display.hpp"
#include "keypad.hpp"
#include "beeper.hpp"
#include "filemanager.hpp"

#include <stack>

class Chip8{
public:
    Chip8(Display* aDisplay, Keypad* aKeypad, Beeper* aBeeper, std::string alternativeFontPath);

    bool loadFont();
    bool loadProgram(std::string programPath);

    uint16_t fetch();
    void execute();
    void updateTimers();
    void playSound();

private:
    DefaultFont defaultFont;
    std::string alternativeFontPath = "";

    Display* display;
    Keypad* keypad;
    Beeper* beeper;
    FileManager fileManager;

    std::stack<uint16_t> stack;
    uint16_t iRegister = 0x0000;
    uint16_t pcRegister = 0x0200;
    uint8_t delayTimer = 0, soundTimer = 0;
    uint8_t varRegisters[16] = {0};
    uint8_t memory[4096];
};
