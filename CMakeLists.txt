cmake_minimum_required(VERSION 3.10)
project(MazeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(maze_generator
    main.cpp
    Cell.cpp
    Maze.cpp
    MazeGenerator.cpp
    MazeSolver.cpp
    MazeRenderer.cpp
)

# Include directories
target_include_directories(maze_generator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
