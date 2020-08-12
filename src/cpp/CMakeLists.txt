project(hello_world)

cmake_minimum_required(VERSION 3.13)
find_package(benchmark REQUIRED)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ggdb")


add_executable(hello hello.cpp)
add_executable(bye bye.cpp)
add_executable(array array.cpp)
add_executable(valarray valarray.cpp)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark benchmark::benchmark)
