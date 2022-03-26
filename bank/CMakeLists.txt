cmake_minimum_required(VERSION 3.17)
project(TestXVector LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(testXVector
    src/testXVector.c src/xvector.c src/xvector.c)
