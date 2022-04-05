cmake_minimum_required(VERSION 3.17)
project(CDAppdbm LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(appdbm src/main.c src/controller.c src/appcommon.h)
target_link_libraries(appdbm dbm)
