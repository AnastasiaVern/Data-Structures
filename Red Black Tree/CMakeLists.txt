cmake_minimum_required(VERSION 3.6)
project(RedBlackTree)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(SOURCE_FILES include/RBTree.hpp include/RBTreeClass.hpp sources/main.cpp)
add_executable(RedBlackTree ${SOURCE_FILES})
