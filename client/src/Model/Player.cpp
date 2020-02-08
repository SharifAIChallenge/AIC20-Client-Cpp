#include "Player.h"

int Player::playerId() const {
    return player_id_;
}

int Player::ap() const {
    return ap_;
}

std::vector<const Spell *> Player::spells() const {
    return spells_;
}

std::vector<const BaseUnit *> Player::hand() const {
    return hand_;
}

std::vector<const BaseUnit *> Player::deck() const {
    return deck_;
}

const King *Player::king() const {
    return king_;
}
