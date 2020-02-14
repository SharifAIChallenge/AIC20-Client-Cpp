#ifndef AIC20_CLIENT_CPP_SPELL_H
#define AIC20_CLIENT_CPP_SPELL_H

#include <string>

#include "enums.h"

class InitMessage;

class Spell {
public:
    Spell() = default;

    ~Spell() = default;

    int getTypeId() const;

    SpellType getType() const;

    int getDuration() const;

    int getPriority() const;

    int getRange() const;

    int getPower() const;

    SpellTarget getTarget() const;

    bool isDamaging() const;

    bool isAreaSpell() const;

    bool isUnitSpell() const;

private:
    int type_id_;
    SpellType type_;
    int duration_;
    int priority_;
    int range_;
    int power_;
    SpellTarget target_;
    bool is_damaging_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_SPELL_H
