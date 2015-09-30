cmake_minimum_required(VERSION 2.6)
add_definitions("-std=c++11")

project(tests)
find_package(Threads)
include_directories(../gtest/include)
link_directories(../gtest)

add_executable(tests test_default_allocator.cpp test_counting_allocator.cpp test_dynamic_array.cpp test_map.cpp test_stack_guard.cpp ../src/engine/data/json_value.cpp ../src/engine/data/json_parser.cpp test_json_parser.cpp tests.cpp)
target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT})

project(sfml)
set(CMAKE_MODULE_PATH "." ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(sfml test_sfml.cpp)
target_link_libraries(sfml ${SFML_LIBRARIES})