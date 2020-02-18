#include "GameConstants.h"

int GameConstants::getMaxAp() const{
    return max_ap_;
}

int GameConstants::getApAddition() const {
    return ap_addition_;
}

int GameConstants::getMaxTurns() const{
    return max_turns_;
}

int GameConstants::getTurnTimeout() const{
    return turn_timeout_;
}

int GameConstants::getPickTimeout() const{
    return pick_timeout_;
}

int GameConstants::getTurnsToUpgrade() const{
    return turns_to_upgrade_;
}

int GameConstants::getTurnsToSpell() const{
    return turns_to_spell_;
}

int GameConstants::getDamageUpgradeAddition() const{
    return damage_upgrade_addition_;
}

int GameConstants::getRangeUpgradeAddition() const{
    return range_upgrade_addition_;
}

int GameConstants::getDeckSize() const {
    return deck_size_;
}

int GameConstants::getHandSize() const {
    return hand_size_;
}
