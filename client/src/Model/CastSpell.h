#ifndef AIC20_CLIENT_CPP_CASTSPELL_H
#define AIC20_CLIENT_CPP_CASTSPELL_H


class CastSpell {
public:
    CastSpell() = default;

    ~CastSpell() = default;

private:
    int caster_id_;
    int type_;
    int id_;//Every casted spell has an ID

    friend class TurnMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_CASTSPELL_H
