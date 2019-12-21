#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>

#include "Cell.h"

class Path {
public:
    Path() = default;

    ~Path() = default;

private:
    int _pathId;
    std::vector<Cell *> _cells;
};


#endif //AIC20_CLIENT_CPP_PATH_H
