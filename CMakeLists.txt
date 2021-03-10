cmake_minimum_required(VERSION 3.17)
project(ALEALEZA C)
set(CMAKE_C_STANDARD 11)

add_executable(ALEALEZA main.c)

target_include_directories(ALEALEZA PRIVATE SDL2-2.0.14/include/)
target_link_directories(ALEALEZA PRIVATE SDL2-2.0.14/lib/x64/)
target_link_libraries(ALEALEZA SDL2 SDL2main)
