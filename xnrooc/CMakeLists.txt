cmake_minimum_required(VERSION 3.17)
project(xnrproj LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(xnrpostfix
    src/xnr_postfix.c src/xnr_parser.c src/xnr_value.h src/xnr_parser.h
)
add_executable(xnrvalue 
    src/xnr_value.c src/xnr_parser.c src/xnr_value.h src/xnr_parser.h)
add_executable(xnrinfix
    src/xnr_infix.c src/xnr_parser.c src/xnr_value.h src/xnr_parser.h)
