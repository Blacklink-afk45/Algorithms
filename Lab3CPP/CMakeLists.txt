# Maze assignment cases live outside the container library.
add_executable(maze_solver main.cpp)
target_link_libraries(maze_solver PRIVATE LibraryCPP)

add_subdirectory(tests)
