#ifndef AIC20_CLIENT_CPP_KING_H
#define AIC20_CLIENT_CPP_KING_H

#include "Cell.h"

class King {
public:
    King() = default;

    ~King() = default;

    Cell center();

private:
    Cell _center;
    int _hp;
    int _level;
    int _attack;
    int _range;
    int _playerId;

    friend class InitMessage;

};


#endif //AIC20_CLIENT_CPP_KING_H
