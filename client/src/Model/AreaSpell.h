#ifndef AIC20_CLIENT_CPP_AREASPELL_H
#define AIC20_CLIENT_CPP_AREASPELL_H

#include "Spell.h"

class AreaSpell : public Spell {
public:
    AreaSpell() = default;

    ~AreaSpell() = default;

private:
    int _range;
    int _power;
    bool _isDamaging;
};


#endif //AIC20_CLIENT_CPP_AREASPELL_H
