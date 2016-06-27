cmake_minimum_required(VERSION 2.8)

project(my_vector.cpp)

include_directories(${MY_VECTOR_SOURCE_DIR})

add_executable(my_vector_testing my_vector_testing.cpp my_vector.cpp my_vector.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")

target_link_libraries(my_vector_testing)


