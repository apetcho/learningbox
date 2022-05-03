cmake_minimum_required(VERSION 3.17)
project(AdvanceC LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Pointers src/pointers.c)
add_executable(NWords src/numword.c)
add_executable(Menuapp src/menuapp.c)
add_executable(StructExple1 src/structExple1.c)
add_executable(StructExple2 src/structExple2.c)
add_executable(TypedefDemo src/createdb.c)
add_executable(
    PersonApp
    src/mainapp.c src/processfile.c src/person.c src/linkedList.c
    src/processfile.h src/person.h src/linkedList.h
)
