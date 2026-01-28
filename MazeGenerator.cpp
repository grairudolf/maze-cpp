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
    // Get unvisited neighbors
    std::vector<std::pair<int, int>> neighbors = maze.getUnvisitedNeighbors(row, col);

    // Shuffle neighbors for randomness and varied branching
    shuffleNeighbors(neighbors);

    // Visit each unvisited neighbor
    for (const auto& neighbor : neighbors) {
        int nextRow = neighbor.first;
        int nextCol = neighbor.second;

        // If neighbor hasn't been visited, carve a path and recurse
        if (!maze.getCell(nextRow, nextCol).isVisited()) {
            // Mark the neighbor cell as a path
            maze.getCell(nextRow, nextCol).setType(Cell::PATH);
            maze.getCell(nextRow, nextCol).setVisited(true);

            // Recursively continue from the neighbor
            recursiveBacktrack(maze, nextRow, nextCol);
        }
    }
    // Backtrack: return to previous cell when no unvisited neighbors exist
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
