add_executable(ALEALEZANY main.c)

target_include_directories(ALEALEZANY PRIVATE ../SDL2-2.0.14/include/)
target_link_directories(ALEALEZANY PRIVATE ../SDL2-2.0.14/lib/x64/)
target_link_libraries(ALEALEZANY SDL2 SDL2main)
