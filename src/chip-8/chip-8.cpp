#include "chip-8.hpp"

Chip8::Chip8(Display* aDisplay, Keypad* aKeypad, Beeper* aBeeper, std::string alternativeFontPath) : display(aDisplay), keypad(aKeypad), beeper(aBeeper), alternativeFontPath(alternativeFontPath) {
    if(!loadFont()){
        throw "Could not load font sprites";
    }
}

bool Chip8::loadFont(){
    if(alternativeFontPath != ""){
        return fileManager.readFile(alternativeFontPath, (char*)memory, 0x50, 0x50 + 80);
    }
    else{
        memcpy((memory + 0x50), defaultFont.font, 80);
        return true;
    }
}

bool Chip8::loadProgram(std::string path){
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
        firstNible = ((instruction >> 12) & 0x0F),
        secondNible = ((instruction >> 8) & 0x0F),
        thirdNible = ((instruction >> 4) & 0x0F),
        fourthNible = (instruction & 0x0F),
        secondByte = (instruction & 0xFF);

    uint16_t immediateAddress = (instruction & 0x0FFF);

    switch(firstNible){
        case 0x0:{
            switch(secondByte){
                case 0xE0:{
                    display->clear();

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
            if(varRegisters[secondNible] == secondByte){
                pcRegister += 2;
            }

            break;
        }
        case 0x4:{
            if(varRegisters[secondNible] != secondByte){
                pcRegister += 2;
            }

            break;
        }
        case 0x5:{
            if(varRegisters[secondNible] == varRegisters[thirdNible]){
                pcRegister += 2;
            }

            break;
        }
        case 0x6:{
            varRegisters[secondNible] = secondByte;

            break;
        }
        case 0x7:{
            varRegisters[secondNible] += secondByte;

            break;
        }
        case 0x8:{
            switch(fourthNible){
                case 0x0:{
                    varRegisters[secondNible] = varRegisters[thirdNible];

                    break;
                }
                case 0x1:{
                    varRegisters[secondNible] |= varRegisters[thirdNible];
                    varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x2:{
                    varRegisters[secondNible] &= varRegisters[thirdNible];
                    varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x3:{
                    varRegisters[secondNible] ^= varRegisters[thirdNible];
                    varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x4:{
                    bool overflow = false;
                    if(varRegisters[secondNible] > 0 && varRegisters[thirdNible] > 0xFF - varRegisters[secondNible]) overflow = true;
                    
                    varRegisters[secondNible] += varRegisters[thirdNible];

                    if(overflow) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;
                    
                    break;
                }
                case 0x5:{
                    bool overflow = false;
                    if(varRegisters[secondNible] >= varRegisters[thirdNible]) overflow = true;

                    varRegisters[secondNible] -= varRegisters[thirdNible];

                    if(overflow) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x6:{
                    uint8_t out = varRegisters[secondNible] & 0x01;
                    
                    varRegisters[secondNible] = varRegisters[thirdNible];
                    varRegisters[secondNible] >>= 1;

                    if(out) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
                case 0x7:{
                    bool overflow = false;
                    if(varRegisters[thirdNible] >= varRegisters[secondNible]) overflow = true;

                    varRegisters[secondNible] = varRegisters[thirdNible] - varRegisters[secondNible];

                    if(overflow) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
                case 0xE:{
                    uint8_t out = varRegisters[secondNible] & 0x80;
                    
                    varRegisters[secondNible] = varRegisters[thirdNible];
                    varRegisters[secondNible] <<= 1;

                    if(out) varRegisters[0xF] = 0x1;
                    else varRegisters[0xF] = 0x0;

                    break;
                }
            }

            break;
        }
        case 0x9:{
            if(varRegisters[secondNible] != varRegisters[thirdNible]){
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
            varRegisters[secondNible] = (rand() % 0xFF) & secondByte;

            break;
        }
        case 0xD:{
            varRegisters[0xF] = 0x0;
            bool pixelOverwritten = display->loadSprite(varRegisters[secondNible] % 64, varRegisters[thirdNible] % 32, (uint8_t*)(memory + iRegister), fourthNible);
            if(pixelOverwritten){
                varRegisters[0xF] = 0x1;
            }

            break;
        }
        case 0xE:{
            switch(secondByte){
                case 0x9E:{
                    if(keypad->isPressed(varRegisters[secondNible])){
                        pcRegister += 2;
                    }

                    break;
                }
                case 0xA1:{
                    if(!keypad->isPressed(varRegisters[secondNible])){
                        pcRegister += 2;
                    }

                    break;
                }
            }

            break;
        }
        case 0xF:{
            switch(secondByte){
                case 0x7:{
                    varRegisters[secondNible] = delayTimer;
                    break;
                }
                case 0x15:{
                    delayTimer = varRegisters[secondNible];

                    break;
                }
                case 0x18:{
                    soundTimer = varRegisters[secondNible];

                    break;
                }
                case 0x1E:{
                    iRegister += varRegisters[secondNible];
                    if(iRegister > 0xFFF){
                        varRegisters[0xF] = 0x1;
                    }

                    break;
                }
                case 0xA:{
                    bool pressed = false;

                    for(int i = 0; i < 0xF; i++){
                        if(keypad->beenPressed(i)){
                            varRegisters[secondNible] = i;

                            pressed = true;
                            break;
                        }
                    }
                    
                    if(!pressed){
                        pcRegister -= 2;
                    }

                    break;
                }
                case 0x29:{
                    iRegister = 0x50 + (varRegisters[secondNible] * 5);

                    break;
                }
                case 0x33:{
                    uint8_t number = varRegisters[secondNible];
                    
                    for(int i = 2; i >= 0; i--){
                        memory[iRegister + i] = number % 10;
                        number /= 10;
                    }

                    break;
                }
                case 0x55:{
                    for(int i = 0; i <= secondNible; i++){
                        memory[iRegister] = varRegisters[i];
                        iRegister++;
                    }

                    break;
                }
                case 0x65:{
                    for(int i = 0; i <= secondNible; i++){
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
        beeper->play();
    }
    else{
        beeper->stop();
    }
}