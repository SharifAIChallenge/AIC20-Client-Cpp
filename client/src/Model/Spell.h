#ifndef AIC20_CLIENT_CPP_SPELL_H
#define AIC20_CLIENT_CPP_SPELL_H

#include <string>

#include "enums.h"

class InitMessage;

class Spell {
public:
    Spell() = default;

    ~Spell() = default;

    int typeId() const;

    SpellType type() const;

    int duration() const;

    int priority() const;

    int range() const;

    int power() const;

    SpellTarget target() const;

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
