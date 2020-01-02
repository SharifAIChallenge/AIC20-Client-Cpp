#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>
#include <Core/Message/Parse/InitMessage.h>

#include "Cell.h"

class Path {
public:
    Path() = default;

    ~Path();//TODO delete the _cells

    int pathId();

    std::vector<Cell *> cells();

private:
    int path_id_;
    std::vector<Cell *> cells_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_PATH_H
