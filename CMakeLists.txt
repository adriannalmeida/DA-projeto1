cmake_minimum_required(VERSION 3.27)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto1
        City.cpp
        City.h
        DataParser.cpp
        data_structures/ufds.cpp
        data_structures/MutablePriorityQueue.h
        Reservoir.h
        Reservoir.cpp
        main.cpp
        Station.cpp)
