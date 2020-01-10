#ifndef AIC20_CLIENT_CPP_PLAYER_H
#define AIC20_CLIENT_CPP_PLAYER_H

#include <vector>

#include "Spell.h"
#include "BaseUnit.h"
#include "King.h"

class InitMessage;

class TurnMessage;

class Player {
public:
    Player() = default;

    ~Player() = default;

    int playerId();

    int ap();

    const King *king();

private:
    int player_id_;
    int ap_;
    std::vector<Spell *> spells_;
    King *king_;

    friend class InitMessage;

    friend class TurnMessage;
};


#endif //AIC20_CLIENT_CPP_PLAYER_H
