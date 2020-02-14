#ifndef AIC20_CLIENT_CPP_CASTSPELL_H
#define AIC20_CLIENT_CPP_CASTSPELL_H

#include "Spell.h"
#include "Cell.h"

class CastSpell {
public:
    CastSpell() = default;

    ~CastSpell() = default;

    int getCasterId() const;

    const Spell *getSpell() const;

    int getId() const;

    const Cell *getCell() const;

    std::vector<const Unit *> getAffectedUnits() const;

private:
    int caster_id_;
    const Spell *spell_;
    int id_;
    const Cell *cell_;
    std::vector<const Unit *> affected_units_;

    friend class TurnMessage;
    friend class ShutdownMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_CASTSPELL_H
