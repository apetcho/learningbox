cmake_minimum_required(VERSION 3.17)
project(AdvanceC LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Pointers src/pointers.c)
add_executable(NWords src/numword.c)
add_executable(Menuapp src/menuapp.c)
