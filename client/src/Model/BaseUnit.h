#ifndef AIC20_CLIENT_CPP_BASEUNIT_H
#define AIC20_CLIENT_CPP_BASEUNIT_H


#include <Core/Message/Parse/InitMessage.h>

class BaseUnit {
public:
    BaseUnit() = default;

    ~BaseUnit() = default;

private:
    int type_; //TODO enum
    int maxHP_;
    int attack_;
    int range_;
    int target_; //TODO enum
    bool isFlying_;
    bool isMultiple_;
    int ap_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_BASEUNIT_H
