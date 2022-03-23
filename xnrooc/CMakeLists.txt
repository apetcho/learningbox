cmake_minimum_required(VERSION 3.17)
project(xnrproj LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(xnrvalue
    src/xnr_value.c src/xnr_name.c src/xnr_variable.c src/xnr_mathlib.c 
    src/xnr_parser.c src/xnr_value.h src/xnr_name.h src/xnr_variable.h
    src/xnr_parser.h src/xnr_bsearch.c src/xnr_bsearch.h
)
