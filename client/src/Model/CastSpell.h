#ifndef AIC20_CLIENT_CPP_CASTSPELL_H
#define AIC20_CLIENT_CPP_CASTSPELL_H


class CastSpell {
public:
    CastSpell() = default;

    ~CastSpell() = default;

private:
    int player_id_;
    int type_;
    int id_;//Every casted spell has an ID

    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_CASTSPELL_H
