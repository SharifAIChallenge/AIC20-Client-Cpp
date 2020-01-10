#ifndef AIC20_CLIENT_CPP_CASTAREASPELL_H
#define AIC20_CLIENT_CPP_CASTAREASPELL_H

#include "CastSpell.h"
#include "Cell.h"

class CastAreaSpell : public CastSpell {
public:
    CastAreaSpell() = default;

    ~CastAreaSpell() = default;

private:
    Cell *center_;
    int remaining_turns_;
};


#endif //AIC20_CLIENT_CPP_CASTAREASPELL_H
