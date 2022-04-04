cmake_minimum_required(VERSION 3.17)
project(DBMTuto LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(dbmExple1 src/example01.c)
target_link_libraries(dbmExple1 dbm)
