#ifndef AIC20_CLIENT_CPP_CASTUNITSPELL_H
#define AIC20_CLIENT_CPP_CASTUNITSPELL_H

#include "CastSpell.h"
#include "Cell.h"

class CastUnitSpell : public CastSpell {
public:
    CastUnitSpell() = default;

    ~CastUnitSpell() = default;

private:
    int _unitId;
    Cell _targetCell;
};


#endif //AIC20_CLIENT_CPP_CASTUNITSPELL_H
