cmake_minimum_required(VERSION 3.6)
project(RandomizedBST)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SOURCE_FILES include/RBST.hpp include/RBSTClass.hpp sources/main.cpp)
add_executable(WordsLadder ${SOURCE_FILES} sources/main.cpp)
