#include "Unit.h"

const Cell *Unit::cell() const {
    return cell_;
}

int Unit::unitId() const {
    return unit_id_;
}

int Unit::playerId() const {
    return player_id_;
}

int Unit::hp() const {
    return hp_;
}

int Unit::damageLevel() const {
    return damage_level_;
}

int Unit::rangeLevel() const {
    return range_level_;
}

int Unit::range() const {
    return range_;
}

int Unit::attack() const {
    return attack_;
}

bool Unit::isDuplicate() const {
    return is_duplicate_;
}

bool Unit::isHasted() const {
    return is_hasted_;
}

const Unit *Unit::target() const {
    return target_;
}

const Cell *Unit::targetCell() const {
    return target_cell_;
}

const King *Unit::targetIfKing() const {
    return target_if_king_;
}

const BaseUnit *Unit::baseUnit() const {
    return base_unit_;
}

const Path *Unit::path() const {
    return path_;
}

const std::vector<const CastSpell *> Unit::affectedSpells() const {
    return affected_spells_;
}
