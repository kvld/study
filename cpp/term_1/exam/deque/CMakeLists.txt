cmake_minimum_required(VERSION 2.8)

project(deque.cpp)

include_directories(${MY_VECTOR_SOURCE_DIR})

add_executable(deque_testing deque_testing.cpp deque.cpp deque.h iterator.cpp const_iterator.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")

target_link_libraries(deque)



