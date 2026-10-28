cmake_minimum_required(VERSION 3.10)
project(LibraryCPP)

set(CMAKE_CXX_STANDARD 11)

add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)

add_subdirectory(Tests)

# add_subdirectory(../Lab3CPP ../Lab3CPP/build)
