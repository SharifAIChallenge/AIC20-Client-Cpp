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
    bool was_cast_this_turn_;//TODO added this
    std::vector<const Unit *> affected_units_;//TODO added this

    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_CASTAREASPELL_H
