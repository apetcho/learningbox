cmake_minimum_required(VERSION 3.17)
project(maze LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(exemaze src/main.c src/maze.c src/maze.h)
target_compile_options(exemaze PUBLIC -Wall)
