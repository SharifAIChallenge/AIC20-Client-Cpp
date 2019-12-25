#ifndef AIC20_CLIENT_CPP_PLAYER_H
#define AIC20_CLIENT_CPP_PLAYER_H

#include <vector>

#include "Spell.h"
#include "BaseUnit.h"

class Player {
public:
    Player() = default;

    ~Player() = default;

private:
    int _playerId;
    int _ap;
    int _upgradeTokens;
    std::vector<Spell *> _spells;
    std::vector<BaseUnit *> _hand;
    std::vector<BaseUnit *> _deck;
};


#endif //AIC20_CLIENT_CPP_PLAYER_H
