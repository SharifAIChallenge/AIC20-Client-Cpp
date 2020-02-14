#ifndef AIC20_CLIENT_CPP_KING_H
#define AIC20_CLIENT_CPP_KING_H

#include "Cell.h"

class Game;

class King {
public:
    King() = default;

//    King(const King &obj);
//
    King operator=(const King&) = delete;

    ~King() = default;

    const Cell *getCenter() const;

    int getHp() const;

    bool isAlive() const;

    int getPlayerId() const;

    int getAttack() const;

    int getRange() const;

    const Unit *getTarget() const;

    const Cell *getTargetCell() const;


private:
    const Cell *center_;
    int hp_;
    bool is_alive_;
    int attack_;
    int range_;
    int player_id_;
    const Unit *target_;
    const Cell *target_cell_;

    friend class InitMessage;
    friend class TurnMessage;
    friend class ShutdownMessage;
    friend class Game;
    friend class Map;
};


#endif //AIC20_CLIENT_CPP_KING_H
