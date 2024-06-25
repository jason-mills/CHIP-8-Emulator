find_package(SDL2 REQUIRED)

add_library(display)
target_sources(display
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/display.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/display.hpp
)
target_include_directories(display
    PRIVATE 
        ${SDL2_INCLUDE_DIRS}
        ../keypad
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(display
    PRIVATE
        SDL2
)