cmake_minimum_required(VERSION 3.12)
project(AES)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("gtest")

add_executable(AES src/main.cpp src/State.h src/State.cpp)
add_executable(tests test/runTests.cpp src/State.h src/State.cpp test/state/StateTest.cpp)

target_link_libraries(tests gtest gtest_main)