project(gtest_sample)

cmake_minimum_required(VERSION 3.13)
find_package(GTest REQUIRED)
#add_subdirectory(gtest/benchmark)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ggdb")

add_executable(test_main src/test_main.cpp)
target_link_libraries(test_main GTest::GTest GTest::Main)
