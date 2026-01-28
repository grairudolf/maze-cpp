#include "Cell.h"

Cell::Cell(int row, int col, CellType type)
    : row(row), col(col), type(type), visited(false) {}
