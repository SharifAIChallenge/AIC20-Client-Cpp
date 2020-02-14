#include "King.h"

const Cell *King::getCenter() const {
    return center_;
}

int King::getHp() const {
    return hp_;
}

bool King::isAlive() const {
    return is_alive_;
}

int King::getPlayerId() const {
    return player_id_;
}

int King::getAttack() const {
    return attack_;
}

int King::getRange() const {
    return range_;
}

const Unit *King::getTarget() const {
    return target_;
}

const Cell *King::getTargetCell() const {
    return target_cell_;
}
