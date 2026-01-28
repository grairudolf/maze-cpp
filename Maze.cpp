#include "Maze.h"
#include <algorithm>

Maze::Maze(int rows, int cols)
    : rows(rows), cols(cols) {
    // Initialize grid with all cells as walls
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = Cell(i, j, Cell::WALL);
        }
    }
}

Cell& Maze::getCell(int row, int col) {
    return grid[row][col];
}

const Cell& Maze::getCell(int row, int col) const {
    return grid[row][col];
}

void Maze::reset() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j].setType(Cell::WALL);
            grid[i][j].setVisited(false);
        }
    }
}

bool Maze::isInBounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

std::vector<std::pair<int, int>> Maze::getNeighbors(int row, int col) const {
    std::vector<std::pair<int, int>> neighbors;

    // Directions: up, down, left, right
    const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];

        if (isInBounds(newRow, newCol)) {
            neighbors.push_back({newRow, newCol});
        }
    }

    return neighbors;
}

std::vector<std::pair<int, int>> Maze::getUnvisitedNeighbors(int row, int col) const {
    std::vector<std::pair<int, int>> neighbors;

    // Directions: up, down, left, right
    const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];

        if (isInBounds(newRow, newCol) && !grid[newRow][newCol].isVisited()) {
            neighbors.push_back({newRow, newCol});
        }
    }

    return neighbors;
}
