cmake_minimum_required(VERSION 3.26)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto1
        City.cpp
        City.h
        DataParser.h
        DataParser.cpp
        data_structures/ufds.cpp
        data_structures/MutablePriorityQueue.h
        Reservoir.h
        Reservoir.cpp
        main.cpp
        Station.cpp
        Utils.h
        Utils.cpp
        menu.cpp
        menu.h
)