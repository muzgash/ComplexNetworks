CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

INCLUDE_DIRECTORIES( include )

ADD_DEFINITIONS( -std=c++11 )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

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

target_link_libraries(opinion degree network node)

ADD_EXECUTABLE( social-impact src/SocialImpact.cpp )
target_link_libraries(social-impact degree network node)
