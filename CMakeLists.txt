cmake_minimum_required(VERSION 3.7)

project(Soneca)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Soneca 
    main.c
)
target_link_libraries(Soneca ${SDL2_LIBRARIES} m)