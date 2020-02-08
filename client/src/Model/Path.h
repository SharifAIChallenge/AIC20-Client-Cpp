#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>

#include "Cell.h"

class InitMessage;

class Path {
public:
    Path() = default;

    Path(const Path&, bool reverse = false);

    bool operator==(const Path &obj);

    ~Path() = default;

    int pathId() const;

    std::vector<const Cell *> cells() const;

private:
    int path_id_;
    std::vector<const Cell *> cells_;

    friend class InitMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_PATH_H
