#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>
#include <Core/Message/Parse/InitMessage.h>

#include "Cell.h"

class Path {
public:
    Path() = default;

    ~Path();//TODO delete the _cells

private:
    int _pathId;
    std::vector<Cell *> _cells;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_PATH_H
