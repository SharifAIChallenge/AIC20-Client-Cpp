#include "Cell.h"

Cell::Cell(int row, int col) : row_(row), col_(col) {}

bool Cell::operator==(const Cell &rhs) const {
    return row_ == rhs.row_ &&
           col_ == rhs.col_;
}

bool Cell::operator!=(const Cell &rhs) const {
    return !(rhs == *this);
}

int Cell::getRow() const {
    return row_;
}

int Cell::getCol() const {
    return col_;
}
