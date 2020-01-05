#ifndef AIC20_CLIENT_CPP_KING_H
#define AIC20_CLIENT_CPP_KING_H

#include "Cell.h"

class King {
public:
    King() = default;

    ~King() = default;

    const Cell *center();

    int hp();

    bool isAlive();

    int playerID();

private:
    Cell center_;
    int hp_;
    bool isAlive_;
    int attack_;
    int range_;
    int playerId_;

    friend class InitMessage;
    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_KING_H
