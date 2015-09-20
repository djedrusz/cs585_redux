cmake_minimum_required(VERSION 2.6)
add_definitions("-std=c++11")

project(tests)
find_package(Threads)
include_directories(../gtest/include)
link_directories(../gtest)

add_executable(tests test_default_allocator.cpp test_counting_allocator.cpp test_dynamic_array.cpp test_map.cpp tests.cpp)
target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT})