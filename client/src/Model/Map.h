#ifndef AIC20_CLIENT_CPP_MAP_H
#define AIC20_CLIENT_CPP_MAP_H

#include <vector>

#include "Path.h"
#include "Unit.h"
#include "King.h"

class Map {
public:
    Map() = default;

    Map(const Map&);

    Map& operator=(const Map&) = delete;

    ~Map();//TODO delete the paths_ units_ kings_

    int rowNum() const;

    int colNum() const;

    std::vector<const Path *> paths() const;

    const Cell *cell(int row, int col) const;

    std::vector<const Unit *> units() const;

    std::vector<const Unit *> diedUnits() const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<Cell *>> cells_;
    std::vector<const Path *> paths_;
    std::vector<const Unit *> units_;
    std::vector<const Unit *> died_units_;

    void initCells();

    void clearUnits();

    friend class InitMessage;

    friend class TurnMessage;

    friend class Game;
};


#endif //AIC20_CLIENT_CPP_MAP_H
