cmake_minimum_required(VERSION 2.8)

project(big_integer.cpp)

include_directories(${BIGINT_SOURCE_DIR})

add_executable(big_integer_testing big_integer_testing.cpp big_integer.h big_integer.cpp custom_vector.h custom_vector.cpp gtest/gtest-all.cc gtest/gtest.h gtest/gtest_main.cc)
#add_executable(big_integer_testing main.cpp big_integer.h big_integer.cpp custom_vector.h custom_vector.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")

target_link_libraries(big_integer_testing)

