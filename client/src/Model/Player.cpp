#include "Player.h"

int Player::playerId() {
    return player_id_;
}

int Player::ap() {
    return ap_;
}

std::vector<const Spell *> Player::spells() {
    return spells_;
}

std::vector<const BaseUnit *> Player::hand() {
    return hand_;
}

std::vector<const BaseUnit *> Player::deck() {
    return deck_;
}

const King *Player::king() {
    return king_;
}
