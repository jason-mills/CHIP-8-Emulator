find_package(SDL2 REQUIRED)

add_library(keypad)
target_sources(keypad
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/keypad.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/keypad.hpp
)
target_include_directories(keypad
    PRIVATE 
        ${SDL2_INCLUDE_DIRS}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(keypad
    PRIVATE
        SDL2
)