add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_subdirectory(chip-8)
add_subdirectory(display)
add_subdirectory(filemanager)
add_subdirectory(keypad)
add_subdirectory(beeper)
target_link_libraries(${CMAKE_PROJECT_NAME}
    chip-8
    display
    filemanager
    keypad
    beeper
)
