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

bool Unit::wasPlayedThisTurn() const {
    return was_played_this_turn_;
}

bool Unit::wasDamageUpgraded() const {
    return was_damage_upgraded_;
}

bool Unit::wasRangeUpgraded() const {
    return was_range_upgraded_;
}

bool Unit::isDuplicate() const {
    return is_duplicate_;
}

bool Unit::isHasted() const {
    return is_hasted_;
}

const Cell *Unit::targetCell() const {
    return target_cell_;
}

const BaseUnit *Unit::baseUnit() const {
    return base_unit_;
}

const Path *Unit::path() const {
    return path_;
}
