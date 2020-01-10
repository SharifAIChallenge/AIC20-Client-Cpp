#ifndef AIC20_CLIENT_CPP_CELL_H
#define AIC20_CLIENT_CPP_CELL_H

#include <vector>
//#include <Core/Message/Parse/InitMessage.h>

class Unit;

class Cell {
public:
    Cell(int row, int col);

    ~Cell() = default;//TODO delete the units_

    bool operator==(const Cell &rhs) const;

    bool operator!=(const Cell &rhs) const;

    int getRow() const;

    int getCol() const;

private:
    int row_;
    int col_;
    std::vector<Unit *> units_;

    //friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_CELL_H
