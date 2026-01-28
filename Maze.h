#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"
#include <vector>
#include <utility>

/**
 * @class Maze
 * @brief Manages the maze grid and provides access to cells
 * 
 * Encapsulates the 2D grid representation and provides methods to
 * manipulate and query the maze structure.
 */
class Maze {
public:
    /**
     * @brief Constructor for a maze with given dimensions
     * @param rows Number of rows in the maze
     * @param cols Number of columns in the maze
     */
    Maze(int rows, int cols);

    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Cell& getCell(int row, int col);
    const Cell& getCell(int row, int col) const;

    // Grid operations
    /**
     * @brief Reset all cells to walls and unvisited state
     */
    void reset();

    /**
     * @brief Check if a coordinate is within maze bounds
     * @param row Row coordinate
     * @param col Column coordinate
     * @return true if within bounds, false otherwise
     */
    bool isInBounds(int row, int col) const;

    /**
     * @brief Get the neighbors of a cell (up, down, left, right)
     * @param row Row coordinate
     * @param col Column coordinate
     * @return Vector of valid neighboring coordinates
     */
    std::vector<std::pair<int, int>> getNeighbors(int row, int col) const;

    /**
     * @brief Get unvisited neighbors of a cell
     * @param row Row coordinate
     * @param col Column coordinate
     * @return Vector of unvisited neighboring coordinates
     */
    std::vector<std::pair<int, int>> getUnvisitedNeighbors(int row, int col) const;

private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> grid;
};

#endif // MAZE_H
