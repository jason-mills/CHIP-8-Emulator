#include "chip-8.hpp"

Chip8::Chip8(Display& aDisplay, Keypad& aKeypad, const Beeper& aBeeper, const std::string& alternativeFontPath) : display(aDisplay), keypad(aKeypad), beeper(aBeeper) {
    if(!loadFont(alternativeFontPath)){
        throw "Could not load font sprites";
    }
}

bool Chip8::loadFont(const std::string& alternativeFontPath){
    if(alternativeFontPath != ""){
        return fileManager.readFile(alternativeFontPath, (char*)memory, 0x50, 0x50 + 80);
    }
    else{
        memcpy((memory + 0x50), defaultFont.font, 80);
        return true;
    }
}

bool Chip8::loadProgram(const std::string& path){
    return fileManager.readFile(path, (char*)memory, 0x200, 4096);
}

uint16_t Chip8::fetch(){
    uint8_t instructionFront = memory[pcRegister];
    uint8_t instructionBack = memory[pcRegister + 1];

    uint16_t instruction = ((uint16_t)instructionFront << 8) | instructionBack;
    pcRegister += 2;

    return instruction;
}

void Chip8::execute(){
    uint16_t instruction = fetch();

    uint8_t 
        firstNibble = ((instruction >> 12) & 0x0F),
        secondNibble = ((instruction >> 8) & 0x0F),
        thirdNibble = ((instruction >> 4) & 0x0F),
        fourthNibble = (instruction & 0x0F),
        secondByte = (instruction & 0xFF);

    uint16_t immediateAddress = (instruction & 0x0FFF);

    switch(firstNibble){
        case 0x0:{
            switch(secondByte){
                case 0xE0:{
                    display.clear();

                    break;
                }
                case 0xEE:{
                    pcRegister = stack.top();
                    stack.pop();

                    break;
                }
            }

            break;
        }
        case 0x1:{
            pcRegister = immediateAddress;

            break;
        }
        case 0x2:{
            stack.push(pcRegister);
            pcRegister = (instruction & immediateAddress);

            break;
        }
        case 0x3:{
            if(varRegisters[secondNibble] == secondByte){
                pcRegister += 2;
            }

            break;
        }
        case 0x4:{
            if(varRegisters[secondNibble] != secondByte){
                pcRegister += 2;
            }

            break;
        }
        case 0x5:{
            if(varRegisters[secondNibble] == varRegisters[thirdNibble]){
                pcRegister += 2;
            }

            break;
        }
        case 0x6:{
            varRegisters[secondNibble] = secondByte;

            break;
        }
        case 0x7:{
            varRegisters[secondNibble] += secondByte;

            break;
        }
        case 0x8:{
            switch(fourthNibble){
                case 0x0:{
                    varRegisters[secondNibble] = varRegisters[thirdNibble];

                    break;
                }
                case 0x1:{
                    varRegisters[secondNibble] |= varRegisters[thirdNibble];
                    varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x2:{
                    varRegisters[secondNibble] &= varRegisters[thirdNibble];
                    varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x3:{
                    varRegisters[secondNibble] ^= varRegisters[thirdNibble];
                    varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x4:{
                    bool overflow = false;
                    if(varRegisters[secondNibble] > 0 && varRegisters[thirdNibble] > 0xFF - varRegisters[secondNibble]) overflow = true;
                    
                    varRegisters[secondNibble] += varRegisters[thirdNibble];

                    if(overflow) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;
                    
                    break;
                }
                case 0x5:{
                    bool overflow = false;
                    if(varRegisters[secondNibble] >= varRegisters[thirdNibble]) overflow = true;

                    varRegisters[secondNibble] -= varRegisters[thirdNibble];

                    if(overflow) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x6:{
                    uint8_t out = varRegisters[secondNibble] & 0x01;
                    
                    varRegisters[secondNibble] = varRegisters[thirdNibble];
                    varRegisters[secondNibble] >>= 1;

                    if(out) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x7:{
                    bool overflow = false;
                    if(varRegisters[thirdNibble] >= varRegisters[secondNibble]) overflow = true;

                    varRegisters[secondNibble] = varRegisters[thirdNibble] - varRegisters[secondNibble];

                    if(overflow) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
                case 0xE:{
                    uint8_t out = varRegisters[secondNibble] & 0x80;
                    
                    varRegisters[secondNibble] = varRegisters[thirdNibble];
                    varRegisters[secondNibble] <<= 1;

                    if(out) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
            }

            break;
        }
        case 0x9:{
            if(varRegisters[secondNibble] != varRegisters[thirdNibble]){
                pcRegister += 2;
            }

            break;
        }
        case 0xA:{
            iRegister = immediateAddress;

            break;
        }
        case 0xB:{
            pcRegister = immediateAddress + varRegisters[0x0];

            break;
        }
        case 0XC:{
            srand((unsigned)time(NULL));
            varRegisters[secondNibble] = (rand() % 0xFF) & secondByte;

            break;
        }
        case 0xD:{
            varRegisters[0xF] = 0x0;
            bool pixelOverwritten = display.loadSprite(varRegisters[secondNibble] % 64, varRegisters[thirdNibble] % 32, (uint8_t*)(memory + iRegister), fourthNibble);
            if(pixelOverwritten){
                varRegisters[0xF] = 0x1;
            }

            break;
        }
        case 0xE:{
            switch(secondByte){
                case 0x9E:{
                    if(keypad.isPressed(varRegisters[secondNibble])){
                        pcRegister += 2;
                    }

                    break;
                }
                case 0xA1:{
                    if(!keypad.isPressed(varRegisters[secondNibble])){
                        pcRegister += 2;
                    }

                    break;
                }
            }

            break;
        }
        case 0xF:{
            switch(secondByte){
                case 0x07:{
                    varRegisters[secondNibble] = delayTimer;
                    break;
                }
                case 0x15:{
                    delayTimer = varRegisters[secondNibble];

                    break;
                }
                case 0x18:{
                    soundTimer = varRegisters[secondNibble];

                    break;
                }
                case 0x1E:{
                    iRegister += varRegisters[secondNibble];
                    if(iRegister > 0xFFF){
                        varRegisters[0xF] = 0x1;
                    }

                    break;
                }
                case 0x0A:{
                    bool pressed = false;

                    for(uint8_t i = 0; i < 0xF; i++){
                        if(keypad.beenPressed(i)){
                            varRegisters[secondNibble] = i;

                            pressed = true;
                            break;
                        }
                    }
                    
                    if(!pressed || keypad.isPressed(varRegisters[secondNibble])){
                        pcRegister -= 2;
                    }

                    break;
                }
                case 0x29:{
                    iRegister = 0x50 + (varRegisters[secondNibble] * 5);

                    break;
                }
                case 0x33:{
                    uint8_t number = varRegisters[secondNibble];
                    
                    for(int i = 2; i >= 0; i--){
                        memory[iRegister + i] = number % 10;
                        number /= 10;
                    }

                    break;
                }
                case 0x55:{
                    for(int i = 0; i <= secondNibble; i++){
                        memory[iRegister] = varRegisters[i];
                        iRegister++;
                    }

                    break;
                }
                case 0x65:{
                    for(int i = 0; i <= secondNibble; i++){
                        varRegisters[i] = memory[iRegister];
                        iRegister++;
                    }
                    
                    break;
                }
            }

            break;
        }
    }
}

void Chip8::updateTimers(){
    if(delayTimer){
        delayTimer--;
    }
    if(soundTimer){
        soundTimer--;
    }
}

void Chip8::playSound(){
    if(soundTimer){
        beeper.play();
    }
    else{
        beeper.stop();
    }
}