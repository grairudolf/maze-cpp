#include "MazeRenderer.h"
#include <iostream>
#include <algorithm>

void MazeRenderer::render(const Maze& maze, int startRow, int startCol, int endRow, int endCol) {
    std::cout << "\n=== Maze ===\n" << std::endl;

    for (int i = 0; i < maze.getRows(); ++i) {
        for (int j = 0; j < maze.getCols(); ++j) {
            const Cell& cell = maze.getCell(i, j);
            char ch = getCellChar(cell, i, j, startRow, startCol, endRow, endCol);
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void MazeRenderer::renderWithPath(const Maze& maze, const std::vector<std::pair<int, int>>& path,
                                  int startRow, int startCol, int endRow, int endCol) {
    std::cout << "\n=== Maze with Solution Path (.) ===\n" << std::endl;

    for (int i = 0; i < maze.getRows(); ++i) {
        for (int j = 0; j < maze.getCols(); ++j) {
            const Cell& cell = maze.getCell(i, j);

            // Check if this cell is on the path
            bool onPath = std::find(path.begin(), path.end(), std::make_pair(i, j)) != path.end();

            char ch = getCellChar(cell, i, j, startRow, startCol, endRow, endCol, onPath);
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

char MazeRenderer::getCellChar(const Cell& cell, int row, int col,
                              int startRow, int startCol, int endRow, int endCol,
                              bool onPath) {
    // Check for start and end cells first
    if (row == startRow && col == startCol) {
        return 'S';
    }
    if (row == endRow && col == endCol) {
        return 'E';
    }

    // If on the solution path (excluding start/end), show as dot
    if (onPath) {
        return '.';
    }

    // Otherwise, show wall or path
    if (cell.getType() == Cell::WALL) {
        return '#';
    } else {
        return ' ';
    }
}
