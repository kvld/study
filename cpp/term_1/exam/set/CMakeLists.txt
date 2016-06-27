cmake_minimum_required(VERSION 2.8)

project(persistent_bst.cpp)

include_directories(${MY_PBST_SOURCE_DIR})

add_executable(persistent_bst_testing persistent_bst.cpp persistent_bst_testing.cpp persistent_bst.h node.h node.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")

target_link_libraries(persistent_bst)
