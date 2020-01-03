#ifndef AIC20_CLIENT_CPP_KING_H
#define AIC20_CLIENT_CPP_KING_H

#include "Cell.h"

class King {
public:
    King() = default;

    ~King() = default;

    const Cell *center();

    int hp();

private:
//    Cel+nter_;
    Cell center_;
    int hp_;
//    int level_;
    int attack_;
    int range_;
    int playerId_;

    friend class InitMessage;

};


#endif //AIC20_CLIENT_CPP_KING_H
