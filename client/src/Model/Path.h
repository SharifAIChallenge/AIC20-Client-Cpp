#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>

#include "Cell.h"

class Path {
public:
    Path() = default;

    ~Path() = default;

    int pathId();

    std::vector<Cell *> cells();

private:
    int path_id_;
    std::vector<Cell *> cells_;
};


#endif //AIC20_CLIENT_CPP_PATH_H
