#ifndef AIC20_CLIENT_CPP_BASEUNIT_H
#define AIC20_CLIENT_CPP_BASEUNIT_H


class BaseUnit {
public:
    BaseUnit() = default;

    ~BaseUnit() = default;

private:
    int _type; //TODO enum
    int _maxHP;
    int _attack;
    int _level;
    int _range;
    int _target; //TODO enum
    bool _isFlying;
    bool _isMultiple;

};


#endif //AIC20_CLIENT_CPP_BASEUNIT_H
