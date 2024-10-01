cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(CHIP-8-Emulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

add_subdirectory(src)