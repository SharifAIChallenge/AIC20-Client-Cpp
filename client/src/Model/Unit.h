#ifndef AIC20_CLIENT_CPP_UNIT_H
#define AIC20_CLIENT_CPP_UNIT_H

#include <Core/Message/Parse/TurnMessage.h>
#include "BaseUnit.h"
#include "Cell.h"
#include "Path.h"

class Unit {
public:
    Unit() = default;

    ~Unit() = default;

    const Cell *cell();

private:
    int _unitId;
    int _hp;
    int _playerId;
    bool _isHasted;
    Cell *_cell;
    BaseUnit _baseUnit;
    Path _path;

    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_UNIT_H
