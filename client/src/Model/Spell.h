#ifndef AIC20_CLIENT_CPP_SPELL_H
#define AIC20_CLIENT_CPP_SPELL_H

#include <string>

class InitMessage;

class Spell {
public:
    Spell() = default;

    ~Spell() = default;

    int typeId() const;

    int range() const;

private:
    int type_id_;
    std::string type_; //TODO enum
    int duration_;
    int priority_;
    int range_;
    int power_;
    std::string target_;//TODO enum

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_SPELL_H
