cmake_minimum_required(VERSION 3.12)
project(AES)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak  -g -Ofast")

add_subdirectory("gtest")

add_executable(AES src/main.cpp src/cipher/State.h src/cipher/State.cpp src/cipher/Cipher.h src/cipher/SBox.h src/key/AESKey.h src/key/AESKey.cpp src/cipher/Arithmetics.h src/key/InvalidKeyLengthException.h src/cipher/Cipher.cpp)
add_executable(tests test/runTests.cpp src/cipher/State.h src/cipher/State.cpp test/StateTest.cpp src/cipher/Cipher.h src/cipher/SBox.h test/SboxTest.cpp src/key/AESKey.h src/key/AESKey.cpp test/cipherTest.cpp src/cipher/Arithmetics.h src/key/InvalidKeyLengthException.h test/keyTest.cpp src/cipher/Cipher.cpp)


target_link_libraries(tests gtest gtest_main)