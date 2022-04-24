cmake_minimum_required(VERSION 3.1)

project(SDLTest)

add_executable(SDLTest
    src/main.cpp
    src/App/CApp.cpp
)

include_directories(SDLTest
    src
    src/App
)

target_link_libraries(SDLTest
    SDL2
    SDL2_ttf
    SDL2_image
    SDL2_mixer
)
