#ifndef AIC20_CLIENT_CPP_CELL_H
#define AIC20_CLIENT_CPP_CELL_H

#include <vector>

class Unit;

class TurnMessage;

class Map;

class Cell {
public:
    Cell(int row, int col);

    Cell(const Cell&);

    ~Cell() = default;

    bool operator==(const Cell &rhs) const;

    bool operator!=(const Cell &rhs) const;

    int getRow() const;

    int getCol() const;

    std::vector<const Unit *> getUnits() const;

private:
    int row_;
    int col_;
    std::vector<const Unit *> units_;

    friend class TurnMessage;
    friend class ShutdownMessage;
    friend class Map;
};


#endif //AIC20_CLIENT_CPP_CELL_H
