cmake_minimum_required(VERSION 3.17)
project(xnrproj LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(xnrstring
    src/main.c src/xnr_string.c src/xnr_string.h  src/xnr_object.h
)
add_executable(xnratom 
    src/main.c src/xnr_atom.c src/xnr_object.c 
    src/xnr_object.h src/xnr_string.h)

