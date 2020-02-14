#include "BaseUnit.h"

int BaseUnit::getTypeId() const {
    return type_id_;
}

int BaseUnit::getMaxHp() const {
    return max_hp_;
}

int BaseUnit::getBaseAttack() const {
    return base_attack_;
}

int BaseUnit::getBaseRange() const {
    return base_range_;
}

UnitTarget BaseUnit::getTargetType() const {
    return target_type_;
}

bool BaseUnit::isFlying() const {
    return is_flying_;
}

bool BaseUnit::isMultiple() const {
    return is_multiple_;
}

int BaseUnit::getAp() const {
    return ap_;
}
