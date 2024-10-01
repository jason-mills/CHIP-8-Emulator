# CHIP-8 Emulator

## Goals
The goal of this project was to create a CHIP-8 Emulator in C++. While completing this project goal I wanted to learn to use CMake and SDL. 

## Struggles
The list of struggles with this project is probably too large to count. Most of those were unrelated to the core implementation details of the project. Understanding the way that SDL operates was the largest hurdle to the project. In particular my desire to have a configurable window size was a time sink. Once I understood that SDL auto scales the textures to the window that problem was solved. The decision to use multiple CMakeList files was one that I made based on various recommendations I found. I like the way that it allows you to specify compilation details for each individual module. I'm going to continue this until I find a compelling reason not to. Another hurdle was getting the correct behavior of all of the instructions. Timendus's chip8-test-suite and the Emulator Development Discord were instrumental in finally implementing all of the right behavior.

## Summary
This project is complete to my liking. While there are many other things that I could do to modify it, I am happy with where it is at. A non-exhaustive list includes: precise instruction timings, adding different keypad layouts, and adding a CHIP-8 snapshot function to the filemanager. 

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
The emulator has a pretty reasonable set of default settings. However, if you want to run programs in a way that is non-default see the help section.
```
$ ./CHIP-8-Emulator -help
```

## References
These are the general resources that I used to complete this project.

I used this guide as my primary resource for building the project. I followed most of the recomendations that this article made.\
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

Timendus's chip8-test-suite is the most exhaustive test for correct behavior that I found.\
https://github.com/Timendus/chip8-test-suite

The Emulator Development Discord can be found here.\
https://discord.com/invite/7nuaqZ2

This set of tutorials was useful for learning various SDL features.\
https://lazyfoo.net/tutorials/SDL/index.php

This article was one of the primary reasons that I chose to use multiple CMake files.\
https://gitlab.com/CLIUtils/modern-cmake/-/tree/master/examples/extended-project
