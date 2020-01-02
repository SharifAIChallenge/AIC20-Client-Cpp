#ifndef AIC20_CLIENT_CPP_BASEUNIT_H
#define AIC20_CLIENT_CPP_BASEUNIT_H


#include <Core/Message/Parse/InitMessage.h>

class BaseUnit {
public:
    BaseUnit() = default;

    ~BaseUnit() = default;

private:
    int type_; //TODO enum
    int _maxHP;
    int _attack;
//    int _level;
    int _range;
    int _target; //TODO enum
    bool _isFlying;
    bool _isMultiple;
    int _ap;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_BASEUNIT_H
