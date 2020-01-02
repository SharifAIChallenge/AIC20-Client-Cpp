#ifndef AIC20_CLIENT_CPP_MAP_H
#define AIC20_CLIENT_CPP_MAP_H

#include <vector>

#include "Path.h"
#include "Unit.h"
#include "King.h"

class Map {
public:
    Map() = default;

    ~Map() = default;

    int width();

    int height();

    std::vector<Path *> paths();

private:
    int width_;
    int height_;
    std::vector<Path *> paths_;
    std::vector<Unit *> units_;
    std::vector<King *> kings_;

};


#endif //AIC20_CLIENT_CPP_MAP_H
