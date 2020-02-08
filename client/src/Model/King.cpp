#include "King.h"

const Cell *King::center() const {
    return center_;
}

int King::hp() const {
    return hp_;
}

bool King::isAlive() const {
    return is_alive_;
}

int King::playerId() const {
    return player_id_;
}

int King::attack() const {
    return attack_;
}

int King::range() const {
    return range_;
}

const Unit *King::target() const {
    return target_;
}

const Cell *King::targetCell() const {
    return target_cell_;
}
