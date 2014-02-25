CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

INCLUDE_DIRECTORIES( include )

ADD_DEFINITIONS( -std=c++11 )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_library(libnode SHARED
include/Node.hpp
src/Node.cpp
)

ADD_EXECUTABLE( sinergy src/Sinergy.cpp )

target_link_libraries(sinergy libnode libnodesis)
