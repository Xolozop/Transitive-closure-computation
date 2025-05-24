cmake_minimum_required(VERSION 3.10)
project(EbertSCC)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
    graph.cpp
    graph.h
    algorithms/*.cpp
    algorithms/*.h
    representations/representation.h
    representations/succ*.cpp
    representations/succ*.h
)


add_executable(SCC ${SOURCES}
        main.cpp)
