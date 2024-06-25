#pragma once

#include <string>

struct HelpText{
    const std::string defaultText = "Incorrect usage. Use -help for more details.";

    const std::string longText = "This is an CHIP-8 Emulator.\n"
    "This is an example of basic usage. For more advanced options and further information see the advanced usage section below.\n\n"

    "Basic Usage:\n"
    "./CHIP-8-Emulator -p <filename>\n\n"

    "Advanced Usage:\n"
    "Default values are used for all of the usage flags except for -p. By including the flags the user defined values are used instead.\n\n"

    "- h or -help:\n"
    "Display this help text\n\n"

    "-p or -program:\n"
    "Specify the filepath to the CHIP-8 program that should be executed.\n\n"

    "-c or -clock:\n"
    "Specify how fast the clock of the CHIP-8 Emulator should execute in Hz. CHIP-8 processors ran at 1 - 4 MHz.\n"
    "But because instructions take many cycles to complete the actual frequency should probably be less than 1 MHz.\n"
    "The default clock speed is 500 Hz.\n\n"

    "-w or -windowWidth:\n"
    "Specify the width of the display window.\n"
    "Because the CHIP-8 display is in a ratio of 2 to 1 (64 pixels wide by 32 pixels tall).\n"
    "The height is calculated automatically to fit this ratio.\n"
    "To maximize the window use 'max' with this flag.\n"
    "The default widow width and height is 640 x 320.\n\n"

    "-f or -font:\n"
    "A default font is provided by the Emulator. However, if you have a program that relies on a custom font\n"
    "or think you have better taste feel free to specify the font file.\n";
};
