#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>

#include "Cell.h"

class InitMessage;

class Path {
public:
    Path() = default;

    ~Path() = default;

    int pathId() const;

    std::vector<const Cell *> cells() const;

private:
    int path_id_;
    std::vector<const Cell *> cells_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_PATH_H
