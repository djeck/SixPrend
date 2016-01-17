project(SixPrend)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

add_executable(sixprend main.c Game/init.c Game/login.c)
install(TARGETS sixprend DESTINATION bin)
target_link_libraries(sixprend ${SDL2_LIBRARIES} -lSDL2_ttf)