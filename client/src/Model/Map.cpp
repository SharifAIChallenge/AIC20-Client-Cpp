#include <cassert>
#include "Map.h"

Map::~Map() {

}

int Map::rowNum() {
    return rows_;
}

int Map::colNum() {
    return cols_;
}

std::vector<const Path *> Map::paths() const {
    return paths_;
}

const Cell *Map::cell(int row, int col) const {
    return cells_[row][col];
}

std::vector<const Unit *> Map::units() {
    return units_;
}

void Map::initCells() {
    assert(cells_.empty());
    for (int row = 0; row < rows_; row++) {
        cells_.emplace_back();
        for (int col = 0; col < cols_; col++)
            cells_[row].push_back(new Cell(row, col));
    }
}

void Map::clearUnits() {
    for (const Unit *unit : units_)
        delete unit;
    units_.clear();

    for (const std::vector<Cell *> &row : cells_)
        for (Cell *cell: row)
            cell->units_.clear();
}
