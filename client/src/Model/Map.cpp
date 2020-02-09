#include <cassert>
#include "Map.h"

Map::Map(const Map &obj) {
    this->rows_ = obj.rows_;
    this->cols_ = obj.cols_;

//    for(std::vector<Cell *> row: obj.cells_){
//        std::vector<Cell *> tmp_row;
//        for(Cell * _cell:row){
//            tmp_row.push_back(
//                    new Cell(*_cell)
//            );
//        }
//        this->cells_.push_back(tmp_row);
//    }
    this->initCells();


    for(const Path *_path: obj.paths_){
        this->paths_.push_back(
                new Path(*_path)
        );
    }

    for(const Unit *_unit: obj.units_){
        this->units_.push_back(
                new Unit(*_unit)
        );
    }

    for(const Unit *_dUnit: obj.died_units_){
        this->died_units_.push_back(
                new Unit(*_dUnit)
        );
    }


}

Map::~Map() {
    for(std::vector<Cell *> row: cells_){
        for(Cell * cell_:row){
            delete cell_;
        }
    }
    for(const Path * path_:paths_){
        delete path_;
    }
    for(const Unit * unit_:units_){
        delete unit_;
    }
    for(const Unit * unit_:died_units_){
        delete unit_;
    }
}

int Map::rowNum() const {
    return rows_;
}

int Map::colNum() const {
    return cols_;
}

std::vector<const Path *> Map::paths() const {
    return paths_;
}

const Cell *Map::cell(int row, int col) const {
    return cells_[row][col];
}

std::vector<const Unit *> Map::units() const {
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

std::vector<const King *> Map::kings() const {
    return kings_;
}
