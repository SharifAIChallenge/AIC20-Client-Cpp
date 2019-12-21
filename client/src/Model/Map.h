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

private:
    int _width;
    int _height;
    std::vector<Path *> _paths;
    std::vector<Unit *> _units;
    std::vector<King *> _kings;

};


#endif //AIC20_CLIENT_CPP_MAP_H
