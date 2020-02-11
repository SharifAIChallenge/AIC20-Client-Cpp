#include <cassert>
#include "Map.h"

Map::Map(const Map &obj) {
    this->rows_ = obj.rows_;
    this->cols_ = obj.cols_;

    this->initCells();//New cells


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

    for(const King *_king: obj.kings_){
        King *tmp_king = new King(*_king);
        tmp_king->center_ = this->cells_[_king->center_->row_][_king->center_->col_];
//        tmp_king->target_  //(Assume it's empty)
//        tmp_king->target_cell_  //(Assume it's empty)
        this->kings_.push_back(tmp_king);
        this->local_kings_.push_back(tmp_king);
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
    for(const King * king_:kings_){
        delete king_;
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

King *Map::give_king_by_playerId(int player_id) {
    for(King * _king:this->local_kings_){
        if(_king->playerId() == player_id){
            return _king;
        }
    }
    assert(0);
}
