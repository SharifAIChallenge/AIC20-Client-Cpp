#include "BaseUnit.h"

int BaseUnit::typeId() const {
    return type_id_;
}

int BaseUnit::maxHp() const {
    return max_hp_;
}

int BaseUnit::baseAttack() const {
    return base_attack_;
}

int BaseUnit::baseRange() const {
    return base_range_;
}

UnitTarget BaseUnit::targetType() const {
    return target_type_;
}

bool BaseUnit::isFlying() const {
    return is_flying_;
}

bool BaseUnit::isMultiple() const {
    return is_multiple_;
}

int BaseUnit::ap() const {
    return ap_;
}
