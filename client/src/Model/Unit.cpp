#include "Unit.h"

const Cell *Unit::getCell() const {
    return cell_;
}

int Unit::getUnitId() const {
    return unit_id_;
}

int Unit::getPlayerId() const {
    return player_id_;
}

int Unit::getHp() const {
    return hp_;
}

int Unit::getDamageLevel() const {
    return damage_level_;
}

int Unit::getRangeLevel() const {
    return range_level_;
}

int Unit::getRange() const {
    return range_;
}

int Unit::getAttack() const {
    return attack_;
}

bool Unit::isDuplicate() const {
    return is_duplicate_;
}

bool Unit::isHasted() const {
    return is_hasted_;
}

const Unit *Unit::getTarget() const {
    return target_;
}

const Cell *Unit::getTargetCell() const {
    return target_cell_;
}

const King *Unit::getTargetIfKing() const {
    return target_if_king_;
}

const BaseUnit *Unit::getBaseUnit() const {
    return base_unit_;
}

const Path *Unit::getPath() const {
    return path_;
}

const std::vector<const CastSpell *> Unit::getAffectedSpells() const {
    return affected_spells_;
}
