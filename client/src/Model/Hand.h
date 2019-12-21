#ifndef AIC20_CLIENT_CPP_HAND_H
#define AIC20_CLIENT_CPP_HAND_H

#include <vector>

#include "BaseUnit.h"

class Hand {
public:
    Hand() = default;

    ~Hand() = default;

private:
    std::vector<BaseUnit *> _units;
};


#endif //AIC20_CLIENT_CPP_HAND_H
