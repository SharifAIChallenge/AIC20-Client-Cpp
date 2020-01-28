#ifndef AIC20_CLIENT_CPP_MAP_H
#define AIC20_CLIENT_CPP_MAP_H

#include <vector>

#include "Path.h"
#include "Unit.h"
#include "King.h"

class Map {
public:
    Map() = default;

    ~Map();//TODO delete the paths_ units_ kings_

    int rowNum() const;

    int colNum() const;

    std::vector<const Path *> paths() const;

    const Cell *cell(int row, int col) const;

    std::vector<const Unit *> units() const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<Cell *>> cells_;
    std::vector<const Path *> paths_;
    std::vector<const Unit *> units_;

    void initCells();

    void clearUnits();

    friend class InitMessage;

    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_MAP_H
