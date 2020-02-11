#include <iostream>
#include "Player.h"


Player::~Player() {
    for(const Path *_path:paths_from_player_)
        delete _path;

    delete path_to_friend;
}

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


bool Player::isAlive() const {
    return king_->isAlive();
}

int Player::getHp() const {
    return king_->hp();
}

int Player::getSpellCount(const Spell *spell) {
    int count = 0;
    for(const Spell* _spell:this->spells_){
        if(_spell->typeId() == spell->typeId()){
            count++;
        }
    }
    return count;
}

std::vector<const Path *> Player::getPathsFromPlayer() const {
    return paths_from_player_;
}

const Path *Player::getPathToFriend() const {
    return path_to_friend;
}

std::vector<const Unit *> Player::getUnits() const {
    return units;
}

CastAreaSpell *Player::getCastAreaSpell() const {
    return cast_area_spell;
}

CastUnitSpell *Player::getCastUnitSpell() const {
    return cast_unit_spell;
}

std::vector<const Unit *> Player::getDuplicateUnits() const {
    return duplicate_units_;
}

std::vector<const Unit *> Player::getHastedUnits() const {
    return hasted_units_;
}

std::vector<const Unit *> Player::getPlayedUnits() const {
    return played_units_;
}

std::vector<const Unit *> Player::getDiedUnits() const {
    return died_units_;
}

Unit *Player::getRangeUpgradedUnit() const {
    return range_upgraded_unit;
}

Unit *Player::getDamageUpgradedUnit() const {
    return damage_upgraded_unit;
}

