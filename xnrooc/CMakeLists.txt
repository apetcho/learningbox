cmake_minimum_required(VERSION 3.17)
project(xnrproj LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(
    xnrproj
    src/main.c src/xnr_bag.c 
    src/xnr_set.c src/xnr_object.c
    src/xnr_set.h  src/xnr_object.h 
)

