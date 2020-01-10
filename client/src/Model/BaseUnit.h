#ifndef AIC20_CLIENT_CPP_BASEUNIT_H
#define AIC20_CLIENT_CPP_BASEUNIT_H

#include <string>

class InitMessage;

class BaseUnit {
public:
    BaseUnit() = default;

    ~BaseUnit() = default;

    int typeId() const;

private:
    int type_id_; //TODO enum
    int max_hp_;
    int base_attack_;
    int base_range_;
    std::string target_; //TODO enum
    bool is_flying_;
    bool is_multiple_;
    int ap_;

    friend class InitMessage;
};


#endif //AIC20_CLIENT_CPP_BASEUNIT_H
