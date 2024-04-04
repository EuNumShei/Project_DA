cmake_minimum_required(VERSION 3.26)
project(Project_DA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_DA
        City.h
        Graph.h
        main.cpp
        Rede.cpp
        Rede.h
        Reservoir.h
        Station.h)

