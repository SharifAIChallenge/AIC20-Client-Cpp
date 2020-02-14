#include <iostream>
#include "Player.h"


Player::~Player() {
    for(const Path *_path:paths_from_player_)
        delete _path;

    delete path_to_friend;
}

int Player::getPlayerId() const {
    return player_id_;
}

int Player::getAp() const {
    return ap_;
}

std::vector<const Spell *> Player::getSpells() const {
    return spells_;
}

std::vector<const BaseUnit *> Player::getHand() const {
    return hand_;
}

std::vector<const BaseUnit *> Player::getDeck() const {
    return deck_;
}

const King *Player::getKing() const {
    return king_;
}


bool Player::isAlive() const {
    return king_->isAlive();
}

int Player::getHp() const {
    return king_->getHp();
}

int Player::getSpellCount(const Spell *spell) const{
    if(spell == nullptr){//give the complete length
        return this->spells_.size();
    }
    int count = 0;
    for(const Spell* _spell:this->spells_){
        if(_spell->getTypeId() == spell->getTypeId()){
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

