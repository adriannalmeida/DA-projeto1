cmake_minimum_required(VERSION 3.27)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto1
        City.cpp
        City.h
        Pipes.cpp)
