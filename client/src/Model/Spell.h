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

    int range() const;

    SpellTarget target() const;

    SpellType type() const;//TODO should we have this function?

private:
    int type_id_;
    SpellType type_;
    int duration_;
    int priority_;
    int range_;
    int power_;
    SpellTarget target_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_SPELL_H
