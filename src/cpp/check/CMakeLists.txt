project(benchmark)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ggdb")

add_executable(vector src/vector.cpp)
