#ifndef AIC20_CLIENT_CPP_CELL_H
#define AIC20_CLIENT_CPP_CELL_H

#include <vector>
#include <Core/Message/Parse/InitMessage.h>

class Unit;

class Cell {
public:
    Cell() = default;

    ~Cell();//TODO delete the _units

private:
    int _row;
    int _column;
    std::vector<Unit *> _units;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_CELL_H
