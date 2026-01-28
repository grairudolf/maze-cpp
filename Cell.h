#ifndef CELL_H
#define CELL_H

/**
 * @class Cell
 * @brief Represents a single cell in the maze grid
 * 
 * Each cell can be a wall or a path, and tracks its position and visited state
 * during maze generation and solving algorithms.
 */
class Cell {
public:
    enum CellType {
        WALL,
        PATH
    };

    /**
     * @brief Constructor for a cell
     * @param row The row coordinate
     * @param col The column coordinate
     * @param type The initial cell type (default: WALL)
     */
    Cell(int row, int col, CellType type = WALL);

    // Getters
    int getRow() const { return row; }
    int getCol() const { return col; }
    CellType getType() const { return type; }
    bool isVisited() const { return visited; }

    // Setters
    void setType(CellType newType) { type = newType; }
    void setVisited(bool v) { visited = v; }

private:
    int row;
    int col;
    CellType type;
    bool visited;
};

#endif // CELL_H
