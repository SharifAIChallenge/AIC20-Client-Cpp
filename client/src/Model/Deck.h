#ifndef AIC20_CLIENT_CPP_DECK_H
#define AIC20_CLIENT_CPP_DECK_H

#include <vector>

#include "BaseUnit.h"

class Deck {
public:
    Deck() = default;

    ~Deck() = default;

private:
    std::vector<BaseUnit *> _units;
};


#endif //AIC20_CLIENT_CPP_DECK_H
