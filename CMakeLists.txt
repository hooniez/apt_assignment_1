cmake_minimum_required(VERSION 3.21)
project(assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(assignment1
        main.cpp
        Node.cpp
        Node.h
        NodeList.cpp
        NodeList.h
        PathPlanner.cpp
        PathPlanner.h
        Types.h
        )
