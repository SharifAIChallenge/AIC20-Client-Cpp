#include "GameConstants.h"

int GameConstants::maxAp() const{
    return max_ap_;
}

int GameConstants::maxTurns() const{
    return max_turns_;
}

int GameConstants::turnTimeout() const{
    return turn_timeout_;
}

int GameConstants::pickTimeout() const{
    return pick_timeout_;
}

int GameConstants::turnsToUpgrade() const{
    return turns_to_upgrade_;
}

int GameConstants::turnsToSpell() const{
    return turns_to_spell_;
}

int GameConstants::damageUpgradeAddition() const{
    return damage_upgrade_addition_;
}

int GameConstants::rangeUpgradeAddition() const{
    return range_upgrade_addition_;
}

int GameConstants::deckSize() const {
    return deck_size_;
}

int GameConstants::handSize() const {
    return hand_size_;
}
