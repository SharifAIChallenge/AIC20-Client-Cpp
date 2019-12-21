#ifndef AIC20_CLIENT_CPP_SPELL_H
#define AIC20_CLIENT_CPP_SPELL_H


class Spell {
public:
    Spell() = default;

    ~Spell() = default;

private:
    int _turnEffect;
    int _type; //TODO enum
};


#endif //AIC20_CLIENT_CPP_SPELL_H
