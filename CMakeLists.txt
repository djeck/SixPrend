cmake_minimum_required(VERSION 2.6)
project(sixquiprend)
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

add_executable(sixquiprend main.c Game/init.c Game/login.c Game/inc.c Game/menu.c Game/mode.c Game/game.c Game/stat.c GUI/textBox.c GUI/text.c )

install(TARGETS sixquiprend RUNTIME DESTINATION bin)
target_link_libraries(sixquiprend -lSDL2 -lSDL2_ttf)