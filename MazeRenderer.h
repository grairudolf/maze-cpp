#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include "Maze.h"
#include <string>
#include <vector>
#include <utility>

/**
 * @class MazeRenderer
 * @brief Renders the maze to ASCII output
 * 
 * Provides methods to display the maze in the console using ASCII characters:
 * - '#' for walls
 * - ' ' (space) for paths
 * - 'S' for start cell
 * - 'E' for end cell
 */
class MazeRenderer {
public:
    /**
     * @brief Render the maze to console
     * @param maze Reference to the maze to render
     * @param startRow Start cell row
     * @param startCol Start cell column
     * @param endRow End cell row
     * @param endCol End cell column
     */
    static void render(const Maze& maze, int startRow, int startCol, int endRow, int endCol);

    /**
     * @brief Render the maze with the solution path highlighted
     * @param maze Reference to the maze
     * @param path Vector of coordinates representing the path
     * @param startRow Start cell row
     * @param startCol Start cell column
     * @param endRow End cell row
     * @param endCol End cell column
     */
    static void renderWithPath(const Maze& maze, const std::vector<std::pair<int, int>>& path,
                               int startRow, int startCol, int endRow, int endCol);

private:
    /**
     * @brief Get the character representation for a cell
     * @param cell The cell to represent
     * @param row Cell row coordinate
     * @param col Cell column coordinate
     * @param startRow Start cell row
     * @param startCol Start cell column
     * @param endRow End cell row
     * @param endCol End cell column
     * @param onPath Whether the cell is on the solution path
     * @return Character representation of the cell
     */
    static char getCellChar(const Cell& cell, int row, int col,
                           int startRow, int startCol, int endRow, int endCol,
                           bool onPath = false);
};

#endif // MAZE_RENDERER_H
