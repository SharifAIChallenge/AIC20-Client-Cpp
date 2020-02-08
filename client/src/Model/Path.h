#ifndef AIC20_CLIENT_CPP_PATH_H
#define AIC20_CLIENT_CPP_PATH_H

#include <vector>

#include "Cell.h"

class InitMessage;

class Path {
public:
    Path() = default;

    Path(const Path&);

    ~Path() = default;

    int id() const;

    std::vector<const Cell *> cells() const;

private:
    int id_;
    std::vector<const Cell *> cells_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_PATH_H
