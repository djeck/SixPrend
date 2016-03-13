cmake_minimum_required(VERSION 2.6)
project(sixquiprend)
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

file(
        GLOB_RECURSE
        source_files
        GUI/*
	Network/*
        Game/*
        main.c
)

add_executable(sixquiprend ${source_files})

install(TARGETS sixquiprend RUNTIME DESTINATION bin)
target_link_libraries(sixquiprend -lSDL2 -lSDL2_ttf -lSDL2_net)
