#include "Spell.h"

int Spell::getTypeId() const {
    return type_id_;
}

int Spell::getRange() const {
    return range_;
}

SpellTarget Spell::getTarget() const {
    return target_;
}

SpellType Spell::getType() const {
    return type_;
}

int Spell::getDuration() const {
    return duration_;
}

int Spell::getPriority() const {
    return priority_;
}

int Spell::getPower() const {
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
