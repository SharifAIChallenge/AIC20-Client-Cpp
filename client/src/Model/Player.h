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

    int playerId() const;

    int ap() const;

    std::vector<const BaseUnit *> hand() const;

    std::vector<const BaseUnit *> deck() const;

    const King *king() const;

    std::vector<const Spell *> spells() const;

private:
    int player_id_;
    int ap_;
    std::vector<const Spell *> spells_; //todo remove?
    std::vector<const BaseUnit *> deck_;
    std::vector<const BaseUnit *> hand_;
    King *king_;

    friend class InitMessage;
    friend class TurnMessage;

    friend class Game;
};


#endif //AIC20_CLIENT_CPP_PLAYER_H
