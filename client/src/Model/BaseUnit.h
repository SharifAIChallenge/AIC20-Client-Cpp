#ifndef AIC20_CLIENT_CPP_BASEUNIT_H
#define AIC20_CLIENT_CPP_BASEUNIT_H

#include <string>

#include "enums.h"

class InitMessage;

class BaseUnit {
public:
    BaseUnit() = default;

    ~BaseUnit() = default;

    int getTypeId() const;

    int getMaxHp() const;

    int getBaseAttack() const;

    int getBaseRange() const;

    UnitTarget getTargetType() const;

    bool isFlying() const;

    bool isMultiple() const;

    int getAp() const;

private:
    int type_id_;
    int max_hp_;
    int base_attack_;
    int base_range_;
    UnitTarget target_type_;
    bool is_flying_;
    bool is_multiple_;
    int ap_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_BASEUNIT_H
