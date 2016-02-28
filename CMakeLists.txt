project(SixPrend)
cmake_minimum_required(VERSION 2.8)


# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

add_executable(sixprend main.c Game/init.c Game/login.c Game/inc.c Game/menu.c Game/mode.c Game/game.c Game/stat.c)
install(TARGETS sixprend DESTINATION bin)
target_link_libraries(sixprend -lSDL2 -lSDL2_ttf)
