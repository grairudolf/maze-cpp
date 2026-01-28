#include "MazeSolver.h"
#include <queue>

bool MazeSolver::isSolvable(Maze& maze, int startRow, int startCol, int endRow, int endCol) {
    // Reset visited flags for the maze
    for (int i = 0; i < maze.getRows(); ++i) {
        for (int j = 0; j < maze.getCols(); ++j) {
            maze.getCell(i, j).setVisited(false);
        }
    }

    // BFS queue: stores coordinates of cells to explore
    std::queue<std::pair<int, int>> q;

    // Start BFS from the start cell
    if (maze.getCell(startRow, startCol).getType() != Cell::PATH) {
        return false; // Start cell must be a path
    }

    q.push({startRow, startCol});
    maze.getCell(startRow, startCol).setVisited(true);

    // BFS exploration
    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        // Check if we reached the end
        if (row == endRow && col == endCol) {
            return true;
        }

        // Explore all neighbors
        std::vector<std::pair<int, int>> neighbors = maze.getNeighbors(row, col);
        for (const auto& neighbor : neighbors) {
            int nextRow = neighbor.first;
            int nextCol = neighbor.second;

            // Check if neighbor is a path and not visited
            if (maze.getCell(nextRow, nextCol).getType() == Cell::PATH &&
                !maze.getCell(nextRow, nextCol).isVisited()) {
                maze.getCell(nextRow, nextCol).setVisited(true);
                q.push({nextRow, nextCol});
            }
        }
    }

    return false; // No path found
}

std::vector<std::pair<int, int>> MazeSolver::findShortestPath(
    Maze& maze, int startRow, int startCol, int endRow, int endCol) {
    
    // Reset visited flags
    for (int i = 0; i < maze.getRows(); ++i) {
        for (int j = 0; j < maze.getCols(); ++j) {
            maze.getCell(i, j).setVisited(false);
        }
    }

    // Parent tracking for path reconstruction
    std::vector<std::vector<std::pair<int, int>>> parent(
        maze.getRows(),
        std::vector<std::pair<int, int>>(maze.getCols(), {-1, -1})
    );

    std::queue<std::pair<int, int>> q;

    // Start BFS
    if (maze.getCell(startRow, startCol).getType() != Cell::PATH) {
        return {}; // Empty path if start is not a path
    }

    q.push({startRow, startCol});
    maze.getCell(startRow, startCol).setVisited(true);

    bool found = false;

    // BFS exploration with parent tracking
    while (!q.empty() && !found) {
        auto [row, col] = q.front();
        q.pop();

        if (row == endRow && col == endCol) {
            found = true;
            break;
        }

        std::vector<std::pair<int, int>> neighbors = maze.getNeighbors(row, col);
        for (const auto& neighbor : neighbors) {
            int nextRow = neighbor.first;
            int nextCol = neighbor.second;

            if (maze.getCell(nextRow, nextCol).getType() == Cell::PATH &&
                !maze.getCell(nextRow, nextCol).isVisited()) {
                maze.getCell(nextRow, nextCol).setVisited(true);
                parent[nextRow][nextCol] = {row, col};
                q.push({nextRow, nextCol});
            }
        }
    }

    if (found) {
        return reconstructPath(parent, endRow, endCol);
    }

    return {}; // Empty path if no solution found
}

std::vector<std::pair<int, int>> MazeSolver::reconstructPath(
    const std::vector<std::vector<std::pair<int, int>>>& parent,
    int endRow, int endCol) {
    
    std::vector<std::pair<int, int>> path;

    int currentRow = endRow;
    int currentCol = endCol;

    // Trace back from end to start using parent pointers
    while (currentRow != -1 && currentCol != -1) {
        path.push_back({currentRow, currentCol});
        auto [parentRow, parentCol] = parent[currentRow][currentCol];
        currentRow = parentRow;
        currentCol = parentCol;
    }

    // Reverse to get path from start to end
    std::reverse(path.begin(), path.end());

    return path;
}
