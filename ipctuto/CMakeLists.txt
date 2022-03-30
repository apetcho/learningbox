cmake_minimum_required(VERSION 3.17)
project(IPCTutorial LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Getlimits src/getlimits.c)
