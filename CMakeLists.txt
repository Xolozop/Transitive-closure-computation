cmake_minimum_required(VERSION 3.23)
project(trans-closure)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
        *.h
        *.cpp
        )


add_executable(trans-clos ${SOURCES}
        main.cpp)
