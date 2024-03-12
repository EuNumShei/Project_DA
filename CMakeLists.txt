cmake_minimum_required(VERSION 3.27)
project(ProjectDA)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project_DA)

add_executable(ProjectDA
        Project_DA/City.h
        Project_DA/Graph.cpp
        Project_DA/Graph.h
        Project_DA/main.cpp
        Project_DA/Rede.cpp
        Project_DA/Rede.h
        Project_DA/Reservoir.h
        Project_DA/Station.h)
