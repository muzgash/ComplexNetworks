CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

INCLUDE_DIRECTORIES( include )

ADD_DEFINITIONS( -std=c++11 )

add_library(node SHARED
include/Node.hpp
src/Node.cpp
)

add_library(degree SHARED
include/Degree.h
src/Degree.cpp
)

add_library(network SHARED
include/Network.h
src/Network.cpp
)

ADD_EXECUTABLE( opinion src/Opinion.cpp )
ADD_EXECUTABLE( opinion src/SocialImpact.cpp )

target_link_libraries(opinion degree network node)
