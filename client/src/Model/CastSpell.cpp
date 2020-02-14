#include "CastSpell.h"

int CastSpell::getCasterId() const {
    return caster_id_;
}

const Spell *CastSpell::getSpell() const {
    return spell_;
}

int CastSpell::getId() const {
    return id_;
}

const Cell *CastSpell::getCell() const {
    return cell_;
}

std::vector<const Unit *> CastSpell::getAffectedUnits() const {
    return affected_units_;
}
