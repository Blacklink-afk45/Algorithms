cmake_minimum_required(VERSION 3.10)

project(MazeSolverProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../LibraryCPP)

add_executable(maze_solver main.cpp)
target_link_libraries(maze_solver PRIVATE LibraryCPP)
add_subdirectory(tests)