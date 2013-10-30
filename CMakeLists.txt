CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

INCLUDE_DIRECTORIES( include )

add_library(degree SHARED
include/degree.h
src/degree.cpp
)

add_library(network SHARED
include/network.h
src/network.cpp
)

ADD_EXECUTABLE( ws src/watts-strogatz.cpp )

ADD_EXECUTABLE( ba src/barabasi-albert.cpp )

target_link_libraries(ws degree network)

target_link_libraries(ba degree network)
