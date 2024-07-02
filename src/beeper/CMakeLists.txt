find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(beeper)
target_sources(beeper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/beeper.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/beeper.hpp
)
target_include_directories(beeper
    PRIVATE 
        ${SDL2_INCLUDE_DIRS}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(beeper
    PRIVATE
        SDL2
        SDL2_mixer
)