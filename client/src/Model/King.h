#ifndef AIC20_CLIENT_CPP_KING_H
#define AIC20_CLIENT_CPP_KING_H

#include "Cell.h"

class King {
public:
    King() = default;

    ~King() = default;

    Cell *center();

    int hp();

private:
    Cell *center_;
    int hp_;
    int level_;
    int attack_;
    int range_;
    int playerId_;

};


#endif //AIC20_CLIENT_CPP_KING_H
