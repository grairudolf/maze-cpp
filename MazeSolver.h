#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "Maze.h"
#include <vector>
#include <utility>

/**
 * @class MazeSolver
 * @brief Verifies maze solvability using BFS (Breadth-First Search)
 * 
 * Tests whether a path exists from the start cell (top-left) to the end cell (bottom-right).
 * Uses BFS for shortest path finding and complete exploration.
 */
class MazeSolver {
public:
    /**
     * @brief Check if the maze is solvable
     * @param maze Reference to the maze to solve
     * @param startRow Starting row
     * @param startCol Starting column
     * @param endRow Target row
     * @param endCol Target column
     * @return true if a path exists from start to end, false otherwise
     */
    bool isSolvable(Maze& maze, int startRow, int startCol, int endRow, int endCol);

    /**
     * @brief Find the shortest path from start to end using BFS
     * @param maze Reference to the maze
     * @param startRow Starting row
     * @param startCol Starting column
     * @param endRow Target row
     * @param endCol Target column
     * @return Vector of coordinates representing the shortest path (empty if no path exists)
     */
    std::vector<std::pair<int, int>> findShortestPath(Maze& maze, int startRow, int startCol, 
                                                       int endRow, int endCol);

private:
    /**
     * @brief Reconstruct path from BFS parent tracking
     * @param parent Map of child -> parent coordinates
     * @param endRow Target row
     * @param endCol Target column
     * @return Vector of coordinates representing the path
     */
    std::vector<std::pair<int, int>> reconstructPath(
        const std::vector<std::vector<std::pair<int, int>>>& parent,
        int endRow, int endCol
    );
};

#endif // MAZE_SOLVER_H
