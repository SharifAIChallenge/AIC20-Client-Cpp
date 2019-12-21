#ifndef AIC20_CLIENT_CPP_CELL_H
#define AIC20_CLIENT_CPP_CELL_H

#include <vector>

class Unit;

class Cell {
public:
    Cell() = default;

    ~Cell() = default;

private:
    int _row;
    int _column;
    std::vector<Unit *> _units;
};


#endif //AIC20_CLIENT_CPP_CELL_H
