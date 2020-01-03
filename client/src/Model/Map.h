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

    int row_num();

    int col_num();

    std::vector<Path *> paths();

private:
    int rows_;
    int cols_;
    std::vector<Path *> paths_;
    std::vector<Unit *> units_;
    std::vector<King *> kings_;

    friend class InitMessage;
    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_MAP_H
