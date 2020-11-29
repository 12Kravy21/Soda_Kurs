cmake_minimum_required(VERSION 3.17)
project(kurs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(kurs
        include/handler.h
        include/menu.h
        src/handler.cpp
        src/main.cpp
        src/menu.cpp)
