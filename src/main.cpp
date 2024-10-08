#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif

#include "chip-8.hpp"
#include "display.hpp"
#include "keypad.hpp"
#include "help.hpp"

#include <chrono>
#include <getopt.h>
#include <iostream>

int main(int argc, char* argv[]){
    int windowWidth = 0;
    double clockSpeed = 1./500;
    std::string programPath = "", fontPath = "";
    
    HelpText helpText;
    struct option arguments[] = {
        {"help", no_argument, 0, 'h'},
        {"program", required_argument, 0, 'p'},
        {"clock", no_argument, 0, 'c'},
        {"windowWidth", no_argument, 0, 'w'},
        {"font", no_argument, 0, 'f'}
    };
    
    int opt;
    int longIndex = 0;
    while((opt = getopt_long(argc, argv, "hp:c:w:f:", arguments, &longIndex)) != -1){
        switch(opt){
            case 'h':{
                std::cout << helpText.longText << std::endl;
                return 0;
            }
            case 'p':{
                programPath = optarg;

                break;
            }
            case 'c':{
                clockSpeed = (1. / (std::atof(optarg)));

                break;
            }
            case 'w':{
                if((std::string)optarg == "max"){
                    windowWidth = -1;
                }
                else{
                    windowWidth = std::atoi(optarg);
                }

                break;
            }
            case 'f':{
                fontPath = optarg;

                break;
            }
        }
    }

    if(programPath == ""){
        std::cout << helpText.defaultText << std::endl;

        return 1;
    }

    Keypad keypad;
    Display display(keypad, windowWidth);
    Beeper beeper;
    Chip8 chip8(display, keypad, beeper, fontPath);
    chip8.loadProgram(programPath);

    using namespace std::chrono;

    auto clockLimit = duration_cast<system_clock::duration>(duration<double>(clockSpeed));
    auto clockStart = system_clock::now();

    auto fpsLimit = duration_cast<system_clock::duration>(duration<double>(1./60));
    auto frameStart = system_clock::now();
    size_t i = 0;
    while(display.isRunning()){
        display.processEvents();

        if(duration_cast<system_clock::duration>(system_clock::now() - clockStart) >= clockLimit){
            chip8.execute();

            clockStart = system_clock::now();
        }

        if(duration_cast<system_clock::duration>(system_clock::now() - frameStart) >= fpsLimit){
            // both the display and the clock registers of chip8 update at the same rate of 60 times per second
            display.update();
            keypad.updatePrevious();
            chip8.updateTimers();
            chip8.playSound();

            frameStart = system_clock::now();
        }
    }

    return 0;
}
