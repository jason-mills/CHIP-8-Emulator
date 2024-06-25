# CHIP-8 Emulator

## Goals
The goal of this project was to create a CHIP-8 Emulator in C++. While completing this project goal I wanted to learn to use CMake and SDL. 

## Struggles
The list of struggles with this project is probably too large to count. Most of those were unrelated to the core implementation details of the project. Understanding the way that SDL operates was the largest hurdle to the project. In particular my desire to have a configurable window size was a time sink. Once I understood that SDL autoscales the textures to the window that problem was solved. The decision to use multiple CMakeList files was one that I made based on various recommendations I found. I like the way that it allows you to specify compilation details for each individual module. I'm going to continue this until I find a compelling reason not to. 

## Summary
This project is complete to my liking. There are many other things that I could do to modify it. A non-exhaustive list includes: precise instruction timings, debugging the window-size time difference, adding different keypad layouts, and adding a CHIP-8 snapshot function to the filemanager. That said, this emulator passed the BonCoder/BestCoder test and Corax89's test which makes me feel that it is at least reasonably complete.

## Usage
### Build
This project can be built with CMake using the below commands.

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Run
To run the executable simply give it a CHIP-8 program file. 
```
$ ./CHIP-8-Emulator -p <filename>
```

### Help
The emulator has a pretty reasonable set of default settings. However, if you want to run programs in a way that is non-default the help section.
```
$ ./CHIP-8-Emulator -help
```

## References
These are the general resources that I used to complete this project.

I used this guide as my primary resource for building the project. I followed most of the reccomendations that this article made.
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

This is where I found the BestCoder CHIP-8 test rom.
https://github.com/daniel5151/AC8E/tree/master/roms

This is corax89's CHIP-8 test rom.
https://github.com/corax89/chip8-test-rom

I used this CHIP-8 Emulator to compare against my own when I was unable to pass the bc_coder test. I should note that this emulator did not pass all of the tests when I ran it.
https://github.com/sarbajitsaha/Chip-8-Emulator/tree/master

This set of tutorials was useful for learning various SDL features.
https://lazyfoo.net/tutorials/SDL/index.php

This article was one of the primary reasons that I chose to use multiple CMake files.
https://gitlab.com/CLIUtils/modern-cmake/-/tree/master/examples/extended-project
