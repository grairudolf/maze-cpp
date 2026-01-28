#include "MazeGenerator.h"
#include <algorithm>
#include <chrono>

MazeGenerator::MazeGenerator(unsigned int seed) {
    if (seed == 0) {
        // Use current time as seed for randomness
        seed = static_cast<unsigned int>(
            std::chrono::system_clock::now().time_since_epoch().count()
        );
    }
    rng.seed(seed);
}

bool MazeGenerator::generateMaze(Maze& maze) {
    // Reset maze to all walls
    maze.reset();

    // Start from top-left corner (0, 0)
    int startRow = 0;
    int startCol = 0;

    // Mark start cell as path
    maze.getCell(startRow, startCol).setType(Cell::PATH);
    maze.getCell(startRow, startCol).setVisited(true);

    // Begin recursive backtracking
    recursiveBacktrack(maze, startRow, startCol);

    // Ensure end cell is a path
    maze.getCell(maze.getRows() - 1, maze.getCols() - 1).setType(Cell::PATH);

    return true;
}

void MazeGenerator::recursiveBacktrack(Maze& maze, int row, int col) {
    // Mark current cell as visited
    maze.getCell(row, col).setVisited(true);

    // Directions: up, down, left, right (moving by 2 cells)
    const int directions[4][2] = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };
    
    // Shuffle directions for randomness
    std::vector<int> dirIndices = {0, 1, 2, 3};
    std::shuffle(dirIndices.begin(), dirIndices.end(), rng);

    // Try each direction
    for (int dirIdx : dirIndices) {
        int newRow = row + directions[dirIdx][0];
        int newCol = col + directions[dirIdx][1];

        // Check if the new cell is within bounds and unvisited
        if (maze.isInBounds(newRow, newCol) && !maze.getCell(newRow, newCol).isVisited()) {
            // Carve path between current cell and new cell (the wall between them)
            int wallRow = row + directions[dirIdx][0] / 2;
            int wallCol = col + directions[dirIdx][1] / 2;
            
            maze.getCell(wallRow, wallCol).setType(Cell::PATH);
            maze.getCell(newRow, newCol).setType(Cell::PATH);

            // Recursively carve from the new cell
            recursiveBacktrack(maze, newRow, newCol);
        }
    }
}

void MazeGenerator::shuffleNeighbors(std::vector<std::pair<int, int>>& neighbors) {
    // Use Fisher-Yates shuffle for randomization
    std::shuffle(neighbors.begin(), neighbors.end(), rng);
}

void MazeGenerator::carvePath(Maze& maze, int row1, int col1, int row2, int col2) {
    // This method is used internally during generation
    maze.getCell(row1, col1).setType(Cell::PATH);
    maze.getCell(row2, col2).setType(Cell::PATH);
}
