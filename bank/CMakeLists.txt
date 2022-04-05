cmake_minimum_required(VERSION 3.17)
project(TestXVector LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(testXVector
    src/testXVector.c src/xvector.c src/xvector.h)

add_library(xvector src/xvector.c src/xvector.h)
add_executable(testMyBk src/testMyBank.c src/mybank.c src/mybank.h 
    src/xvector.h)
target_link_libraries(testMyBk dbm)
target_link_libraries(testMyBk xvector)
