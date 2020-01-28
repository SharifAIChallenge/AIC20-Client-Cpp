#ifndef AIC20_CLIENT_CPP_CASTUNITSPELL_H
#define AIC20_CLIENT_CPP_CASTUNITSPELL_H

#include "CastSpell.h"
#include "Cell.h"

class CastUnitSpell : public CastSpell {
public:
    CastUnitSpell() = default;

    ~CastUnitSpell() = default;

private:
    int unit_id_;
    int path_id_;
    Cell* target_cell_;

    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_CASTUNITSPELL_H
