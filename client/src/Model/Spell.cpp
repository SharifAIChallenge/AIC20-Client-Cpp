#include "Spell.h"

int Spell::typeId() const {
    return type_id_;
}

int Spell::range() const {
    return range_;
}

SpellTarget Spell::target() const {
    return target_;
}

SpellType Spell::type() const {
    return type_;
}

int Spell::duration() const {
    return duration_;
}

int Spell::priority() const {
    return priority_;
}

int Spell::power() const {
    return power_;
}

bool Spell::isDamaging() const {
    return is_damaging_;
}

bool Spell::isAreaSpell() const {
    return type_ != TELE;
}

bool Spell::isUnitSpell() const {
    return type_ == TELE;
}
