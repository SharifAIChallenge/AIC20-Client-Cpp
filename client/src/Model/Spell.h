#ifndef AIC20_CLIENT_CPP_SPELL_H
#define AIC20_CLIENT_CPP_SPELL_H


#include <Core/Message/Parse/InitMessage.h>

class Spell {
public:
    Spell() = default;

    ~Spell() = default;

private:
    int turnEffect_;
    int type_; //TODO enum
    int duration_;
    int priority_;
    int range_;
    int power_;
    int target_;//TODO enum

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_SPELL_H
