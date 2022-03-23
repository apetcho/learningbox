cmake_minimum_required(VERSION 3.17)
project(xnrproj LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(xnrpoint
    src/testPoint.c 
    src/xnr_point.c src/xnr_object.c src/xnr_object.h src/xnr_point.h
)
add_executable(xnrcirle 
    src/testCircle.c src/xnr_circle.c 
    src/xnr_point.c src/xnr_object.c
    src/xnr_circle.h src/xnr_point.h
    src/xnr_object.h)
