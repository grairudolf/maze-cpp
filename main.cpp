#include "Maze.h"
#include "Cell.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "MazeRenderer.h"
#include <iostream>
#include <chrono>

/**
 * @brief Main function: generates, validates, and displays a maze
 * 
 * This program demonstrates:
 * 1. Creating a configurable maze
 * 2. Generating a perfect maze using recursive backtracking (DFS)
 * 3. Verifying solvability using BFS
 * 4. Rendering the maze and solution path to console
 * 5. Clean OOP design with separation of concerns
 */
int main() {
    std::cout << "=== Complex Maze Generator ===" << std::endl;
    std::cout << "A guaranteed-solvable perfect maze with OOP design\n" << std::endl;

    // Get maze dimensions from user
    int rows, cols;
    std::cout << "Enter maze dimensions:" << std::endl;
    std::cout << "Rows (odd number recommended for better structure): ";
    std::cin >> rows;
    std::cout << "Columns (odd number recommended for better structure): ";
    std::cin >> cols;

    // Validate input
    if (rows < 3 || cols < 3) {
        std::cerr << "Error: Minimum maze size is 3x3" << std::endl;
        return 1;
    }

    // Ensure odd dimensions for better maze structure
    if (rows % 2 == 0) rows++;
    if (cols % 2 == 0) cols++;

    std::cout << "\nUsing dimensions: " << rows << " x " << cols << std::endl;

    // Create the maze
    Maze maze(rows, cols);

    // Generate the maze with a seed for reproducibility
    // Use 0 for random seed, or provide a specific seed for reproducible results
    std::cout << "\nGenerating maze using Recursive Backtracking (DFS)..." << std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();

    MazeGenerator generator(42); // Fixed seed for reproducibility; use 0 for random
    generator.generateMaze(maze);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Maze generated in " << duration.count() << " ms" << std::endl;

    // Define start and end positions
    int startRow = 0, startCol = 0;
    int endRow = rows - 1, endCol = cols - 1;

    // Render the maze without solution
    std::cout << "\n========================================" << std::endl;
    std::cout << "   GENERATED MAZE (Before Solving)" << std::endl;
    std::cout << "========================================" << std::endl;
    MazeRenderer::render(maze, startRow, startCol, endRow, endCol);
    std::cout << std::flush;

    // Verify solvability
    std::cout << "Verifying maze solvability..." << std::endl;

    MazeSolver solver;
    bool solvable = solver.isSolvable(maze, startRow, startCol, endRow, endCol);

    if (solvable) {
        std::cout << "✓ Maze is SOLVABLE" << std::endl;

        // Find and display the shortest path
        std::cout << "\nFinding shortest path from S to E..." << std::endl;
        auto path = solver.findShortestPath(maze, startRow, startCol, endRow, endCol);

        std::cout << "Shortest path length: " << path.size() << " cells" << std::endl;

        // Render the maze with the solution path
        std::cout << "\n========================================" << std::endl;
        std::cout << "   MAZE WITH SOLUTION PATH (.)" << std::endl;
        std::cout << "========================================" << std::endl;
        MazeRenderer::renderWithPath(maze, path, startRow, startCol, endRow, endCol);
        std::cout << std::flush;
    } else {
        std::cerr << "\n✗ ERROR: Maze is NOT solvable! (This should never happen)" << std::endl;
        return 1;
    }

    // Display statistics
    std::cout << "\n=== Maze Statistics ===" << std::endl;
    std::cout << "Dimensions: " << rows << " x " << cols << std::endl;
    std::cout << "Total cells: " << (rows * cols) << std::endl;

    int wallCount = 0, pathCount = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze.getCell(i, j).getType() == Cell::WALL) {
                wallCount++;
            } else {
                pathCount++;
            }
        }
    }

    std::cout << "Walls: " << wallCount << std::endl;
    std::cout << "Paths: " << pathCount << std::endl;
    std::cout << "Path ratio: " << (100.0 * pathCount / (rows * cols)) << "%" << std::endl;

    std::cout << "\n=== Legend ===" << std::endl;
    std::cout << "S = Start (top-left)" << std::endl;
    std::cout << "E = End (bottom-right)" << std::endl;
    std::cout << "# = Wall" << std::endl;
    std::cout << "  = Path (empty space)" << std::endl;
    std::cout << ". = Solution path" << std::endl;

    std::cout << "\nMaze generation complete!" << std::endl;

    return 0;
}
