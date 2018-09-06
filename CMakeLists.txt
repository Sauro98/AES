cmake_minimum_required(VERSION 3.12)
project(AES)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("gtest")

add_executable(AES src/main.cpp src/State.h src/State.cpp src/Cipher.h src/SBox.h src/Key/AESKey.h src/Key/AESKey.cpp src/Arithmetics.h src/Key/InvalidKeyLengthException.h src/Cipher.cpp)
add_executable(tests test/runTests.cpp src/State.h src/State.cpp test/StateTest.cpp src/Cipher.h src/SBox.h test/SboxTest.cpp src/Key/AESKey.h src/Key/AESKey.cpp test/cipherTest.cpp src/Arithmetics.h src/Key/InvalidKeyLengthException.h test/keyTest.cpp src/Cipher.cpp)

target_link_libraries(tests gtest gtest_main)