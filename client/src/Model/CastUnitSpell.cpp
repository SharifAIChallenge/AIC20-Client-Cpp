#include "CastUnitSpell.h"

const Unit *CastUnitSpell::getUnit() const {
    return unit_;
}

const Path *CastUnitSpell::getPath() const {
    return path_;
}
