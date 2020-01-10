#include "Player.h"

int Player::playerId() {
    return player_id_;
}

int Player::ap() {
    return ap_;
}

const King *Player::king() {
    return king_;
}
