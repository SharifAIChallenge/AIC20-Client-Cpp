#ifndef AIC20_CLIENT_CPP_KING_H
#define AIC20_CLIENT_CPP_KING_H

#include "Cell.h"

class Game;

class King {
public:
    King() = default;

    ~King() = default;

    const Cell *center() const;

    int hp() const;

    bool isAlive() const;

    int playerId() const;

    int attack() const;

    int range() const;


private:
    Cell *center_;
    int hp_;
    bool is_alive_;
    int attack_;
    int range_;
    int player_id_;
    int target_id_;

    friend class InitMessage;
    friend class TurnMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_KING_H
