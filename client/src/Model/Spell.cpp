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
