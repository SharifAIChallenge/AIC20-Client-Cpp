#include "CastSpell.h"

int CastSpell::casterId() const {
    return caster_id_;
}

const Spell *CastSpell::spell() const {
    return spell_;
}

int CastSpell::id() const {
    return id_;
}

const Cell *CastSpell::cell() const {
    return cell_;
}

std::vector<const Unit *> CastSpell::affectedUnits() const {
    return affected_units_;
}
