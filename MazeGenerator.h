#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "Maze.h"
#include <random>
#include <vector>

/**
 * @class MazeGenerator
 * @brief Generates a perfect maze using recursive backtracking (DFS)
 * 
 * Uses depth-first search with backtracking to create a maze where:
 * - Exactly one path exists between any two points (perfect maze)
 * - The maze is fully connected (no isolated regions)
 * - All cells are reachable from the start
 */
class MazeGenerator {
public:
    /**
     * @brief Constructor for the maze generator
     * @param seed Random seed for reproducibility (0 = random seed)
     */
    explicit MazeGenerator(unsigned int seed = 0);

    /**
     * @brief Generate a maze using recursive backtracking
     * @param maze Reference to the Maze object to populate
     * @return true if generation was successful
     */
    bool generateMaze(Maze& maze);

private:
    std::mt19937 rng;

    /**
     * @brief Recursive backtracking algorithm to carve paths
     * @param maze Reference to the maze being generated
     * @param row Current row position
     * @param col Current column position
     */
    void recursiveBacktrack(Maze& maze, int row, int col);

    /**
     * @brief Shuffle a vector of neighbor coordinates
     * @param neighbors Vector of coordinates to shuffle
     */
    void shuffleNeighbors(std::vector<std::pair<int, int>>& neighbors);

    /**
     * @brief Check if two cells should be connected (carve a path between them)
     * @param row1 Row of first cell
     * @param col1 Column of first cell
     * @param row2 Row of second cell
     * @param col2 Column of second cell
     * @param maze Reference to the maze
     */
    void carvePath(Maze& maze, int row1, int col1, int row2, int col2);
};

#endif // MAZE_GENERATOR_H
