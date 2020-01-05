#ifndef AIC20_CLIENT_CPP_PLAYER_H
#define AIC20_CLIENT_CPP_PLAYER_H

#include <vector>

#include "Spell.h"
#include "BaseUnit.h"
#include "King.h"

class Player {
public:
    Player() = default;

    ~Player() = default;

    int playerId();

    int ap();


//    std::vector<BaseUnit *> hand_();
//    std::vector<BaseUnit *> deck_();

    King king();

private:
    int player_id_;
    int ap_;
    std::vector<Spell *> spells_;
//    std::vector<BaseUnit *> hand_;
//    std::vector<BaseUnit *> deck_;
    King king_;
};


#endif //AIC20_CLIENT_CPP_PLAYER_H
