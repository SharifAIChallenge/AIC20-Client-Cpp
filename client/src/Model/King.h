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

    const Cell *center() const;

    int hp() const;

    bool isAlive() const;

    int playerId() const;

    int attack() const;

    int range() const;

    const Unit *target() const;

    const Cell *targetCell() const;


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
