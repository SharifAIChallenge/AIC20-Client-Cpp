//───────────────────────────────────────
//───────WHAT─ARE─YOU─DOING─HERE?────────
//───────────────────────────────────────
//───────────────────████████────────────
//──────────────────███▄███████──────────
//──────────────────███████████──────────
//──────────────────███████████──────────
//──────────────────██████───────────────
//──────────────────█████████────────────
//────────█───────███████────────────────
//────────██────████████████─────────────
//────────███──██████████──█─────────────
//────────███████████████────────────────
//────────███████████████────────────────
//─────────█████████████─────────────────
//──────────███████████──────────────────
//────────────████████───────────────────
//─────────────███──██───────────────────
//─────────────██────█───────────────────
//─────────────█─────█───────────────────
//─────────────██────██──────────────────
//───────────────────────────────────────
//───────────GET─BACK─TO─WORK────────────
//───────────────────────────────────────


#include <Core/Message/Create/CreateCastSpellMessage.h>
#include <Core/Message/Create/CreateRangeUpgradeMessage.h>
#include <Utility/Logger.h>
#include "Game.h"

#include "Utility/Utility.h"
#include "Core/Message/Create/CreatePutUnitMessage.h"
#include "Core/Message/Create/CreateCastSpellMessage.h"
#include "Core/Message/Create/CreatePickMessage.h"
#include "Core/Message/Create/CreateRangeUpgradeMessage.h"
#include "Core/Message/Create/CreateDamageUpgradeMessage.h"

Game::Game(EventQueue &event_queue) : event_queue_(event_queue) {
    for(int i=0; i < 4; i++){
        players_[i].player_id_ = i;
    }

}

Game::Game(const Game& obj) :
        event_queue_(obj.event_queue_),
        map_(obj.map_),
        start_time_(obj.start_time_),
        current_turn_(obj.current_turn_),
        available_damage_upgrades_(obj.available_damage_upgrades_),
        available_range_upgrades_(obj.available_range_upgrades_),
        got_damage_upgrade_(obj.got_damage_upgrade_),
        got_range_upgrade_(obj.got_range_upgrade_),
        second_enemy_id_(obj.second_enemy_id_),
        first_enemy_id_(obj.first_enemy_id_),
        friend_id_(obj.friend_id_),
        my_id_(obj.my_id_)
{
    this->game_constants_ = obj.game_constants_;
    for(const BaseUnit * _bUnit:obj.base_units_) {
        this->base_units_.push_back(new BaseUnit(*_bUnit));
    }

    for(const Spell * _spell:obj.spells_) {
        this->spells_.push_back(new Spell(*_spell));
    }

    for(int i = 0; i < 4; i++) {
        this->players_[i].player_id_ = obj.players_[i].player_id_;
        this->players_[i].ap_ = obj.players_[i].ap_;
        this->players_[i].king_ = this->map_.give_king_by_playerId(obj.players_[i].king_->getPlayerId());//The center_ pointer is still on the old one

        this->players_[i].king_->center_ = this->map_.cell(
                obj.players_[i].king_->center_->getRow(),
                obj.players_[i].king_->center_->getCol()
        );

        for(const Spell *_spell: obj.players_[i].spells_){
            this->players_[i].spells_.push_back(
                    this->give_spell_by_typeId(_spell->getTypeId())
            );
        }

        for(const BaseUnit *_bUnit_deck: obj.players_[i].deck_) {
            this->players_[i].deck_.push_back(this->base_units_[_bUnit_deck->getTypeId()]);
        }

        for(const BaseUnit *_bUnit_hand: obj.players_[i].hand_) {
            this->players_[i].hand_.push_back(this->base_units_[_bUnit_hand->getTypeId()]);
        }

//        This part will be in Game::initPlayerData()
//        for(const Path *_path: obj.players_[i].paths_from_player_) {
//            this->players_[i].paths_from_player_.push_back()
//        }
    }
    this->initPlayerData();


}

Game::~Game() {
    for(const BaseUnit * _bUnit:this->base_units_) {
        delete _bUnit;
    }

    for(const Spell * _spell:this->spells_) {
        delete _spell;
    }

}

void Game::initPlayerData() {

    for (int player_id = 0; player_id < 4; player_id++) {
        int friend_id_ = player_id ^ 2;

        for (const Path *path : map_.getPaths()) {
            if (*path->getCells()[0] == *players_[player_id].getKing()->getCenter() &&
                *path->getCells().back() != *players_[friend_id_].getKing()->getCenter()) {
                this->players_[player_id].paths_from_player_.push_back(
                        new Path(*path, false)//This part will be handled by the Player destructor
                );
            } else if (*path->getCells().back() == *players_[player_id].getKing()->getCenter() &&
                     *path->getCells()[0] != *players_[friend_id_].getKing()->getCenter()) {
                this->players_[player_id].paths_from_player_.push_back(
                        new Path(*path, true)//This part will be handled by the Player destructor
                );
            } else if (*path->getCells()[0] == *players_[player_id].getKing()->getCenter() &&
                       *path->getCells().back() == *players_[friend_id_].getKing()->getCenter()){
                this->players_[player_id].path_to_friend = new Path(*path, false);//This part will be handled by the Player destructor
            } else if (*path->getCells().back() == *players_[player_id].getKing()->getCenter() &&
                       *path->getCells()[0] == *players_[friend_id_].getKing()->getCenter()) {
                this->players_[player_id].path_to_friend = new Path(*path, true);//This part will be handled by the Player destructor
            }
        }
    }
}

int Game::currentTurn() {
    return current_turn_;
}


void Game::chooseHandById(std::vector<int> type_ids) {
    event_queue_.push(CreatePickMessage(type_ids));
}

void Game::chooseHand(std::vector<const BaseUnit *> baseUnits) {
    std::vector<int> type_ids;
    for(const BaseUnit* _baseU:baseUnits){
        type_ids.push_back(_baseU->getTypeId());
    }
    event_queue_.push(CreatePickMessage(type_ids));
}


const Player *Game::getMe() {
    return &players_[my_id_];
}

const Player *Game::getFriend() {
    return &players_[friend_id_];
}

const Player *Game::getFirstEnemy() {
    return &players_[first_enemy_id_];
}

const Player *Game::getSecondEnemy() {
    return &players_[second_enemy_id_];
}


const Map *Game::getMap() {
    return &map_;
}

//CANT
std::vector<const Path *> Game::getPathsCrossingCell(const Cell *cell) {
    std::vector<const Path *> cross;
    for (const Path *path : map_.getPaths())
        for (const Cell *c : path->getCells())
            if (*c == *cell) {
                cross.push_back(path);
                break;
            }

    return cross;
}

std::vector<const Path *> Game::getPathsCrossingCell(int row, int col) {
    std::vector<const Path *> cross;
    for (const Path *path : map_.getPaths())
        for (const Cell *c : path->getCells())
            if (c->getRow() == row && c->getCol() == col) {
                cross.push_back(path);
                break;
            }

    return cross;
}

//CANT
std::vector<const Unit *> Game::getCellUnits(const Cell *cell) {
    std::vector<const Unit *> units;

    for (const Unit *unit : map_.getUnits())
        if (*unit->getCell() == *cell)
            units.push_back(unit);

    return units;
}

std::vector<const Unit *> Game::getCellUnits(int row, int col) {
    std::vector<const Unit *> units;

    for (const Unit *unit : map_.getUnits())
        if (unit->getCell()->getRow() == row &&
                unit->getCell()->getCol() == col)
            units.push_back(unit);

    return units;
}

//CANT
const Path *Game::getShortestPathToCell(const Player* from_player,const Cell* cell) {

    //First check if it's on a friends path
    int friend_id = give_friends_id(from_player->player_id_);
    for(int i = 0; i < from_player->path_to_friend->getCells().size(); i++){
        if(*from_player->path_to_friend->getCells()[i] == *cell){
            //Find the players friend
            return players_[friend_id].getPathsFromPlayer()[0];
        }
    }

    //Second check if it's on a enemies friends path
    std::vector<const Path *> player_paths = from_player->getPathsFromPlayer();
    std::vector<const Path *> friend_paths = players_[friend_id].getPathsFromPlayer();
    size_t min = 0x7fffffff;
    const Path *shortest = nullptr;
    size_t path_dist_to_friend = from_player->path_to_friend->cells_.size();

    int first_enemy_id = give_an_enemy_id(from_player->player_id_);
    int second_enemy_id = give_friends_id(first_enemy_id);
    size_t enemy_friend_path_dist = players_[first_enemy_id].path_to_friend->getCells().size();
    for(int i = 0; i < enemy_friend_path_dist; i++){
        if(*players_[first_enemy_id].path_to_friend->getCells()[i] == *cell){//From here we are sure that we have to
            // return the function in this part
            for(const Path *_path: player_paths){
                if(*_path->cells_.back() == *players_[first_enemy_id].king_->center_ &&
                   _path->cells_.size() + i < min){
                    shortest = _path;
                    min = _path->cells_.size() + i;
                }
            }
            for(const Path *_path: friend_paths){
                if(*_path->cells_.back() == *players_[first_enemy_id].king_->center_ &&
                    _path->cells_.size() + path_dist_to_friend - 1 + i < min){
                    shortest = _path;
                    min = _path->cells_.size() + path_dist_to_friend - 1 + i;
                }
            }

            int j =(int) enemy_friend_path_dist -i -1;//Dist of the path from the other side (second Enemy)
            for(const Path *_path: player_paths){
                if(*_path->cells_.back() == *players_[second_enemy_id].king_->center_ &&
                   _path->cells_.size() + j < min){
                    shortest = _path;
                    min = _path->cells_.size() + j;
                }
            }
            for(const Path *_path: friend_paths){
                if(*_path->cells_.back() == *players_[second_enemy_id].king_->center_ &&
                   _path->cells_.size() + path_dist_to_friend - 1 + j < min){
                    shortest = _path;
                    min = _path->cells_.size() + path_dist_to_friend - 1 + j;
                }
            }

            return shortest;
        }
    }

    //Third check the paths form the player
    for (const Path *path : player_paths) {
        for (size_t i = 0; i < path->getCells().size(); i++) {
            if (*path->getCells()[i] == *cell) {
                if (i < min) {
                    min = i;
                    shortest = path;
                }
            }
        }
    }

    //Forth check the paths form the players friend
    for (const Path *path : friend_paths) {
        for (size_t i = 0; i < path->getCells().size(); i++) {
            if (*path->getCells()[i] == *cell) {
                if (i + path_dist_to_friend - 1 < min) {
                    min = i + path_dist_to_friend - 1;//The minus one is to avoid double counting the friends king getCell
                    shortest = path;
                }
            }
        }
    }

    return shortest;
}

const Path *Game::getShortestPathToCell(const Player* from_player, int row, int col) {

    return this->getShortestPathToCell(from_player, map_.cell(row,col));
}


void Game::putUnit(int typeId, int pathId) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, typeId, pathId));
}

void Game::putUnit(const BaseUnit* baseUnit, int pathId) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, baseUnit->getTypeId(), pathId));
}

void Game::putUnit(int typeId, const Path* path) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, typeId, path->getId()));
}

void Game::putUnit(const BaseUnit* baseUnit, const Path* path) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, baseUnit->getTypeId(), path->getId()));
}


int Game::getCurrentTurn() {
    return current_turn_;
}


int Game::getRemainingTime() {
    int duration = getTime();

    if (current_turn_ == 0)
        return getPickTimeout() - (duration - start_time_);
    else
        return getTurnTimeout() - (duration - start_time_);
}


void Game::castUnitSpell(int unitId, int pathId, const Cell *cell, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, const Cell *cell, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), row, col, unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, unitId, pathId));
}


void Game::castUnitSpell(int unitId, const Path *path, const Cell *cell, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), cell->getRow(), cell->getCol(), unitId, path->getId()));
}

void Game::castUnitSpell(int unitId, const Path *path, const Cell *cell, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unitId, path->getId()));
}

void Game::castUnitSpell(int unitId, const Path *path, int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), row, col, unitId, path->getId()));
}

void Game::castUnitSpell(int unitId, const Path *path, int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, unitId, path->getId()));
}

void Game::castUnitSpell(const Unit *unit, int pathId, const Cell *cell, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), cell->getRow(), cell->getCol(), unit->getUnitId(), pathId));
}

void Game::castUnitSpell(const Unit *unit, int pathId, const Cell *cell, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unit->getUnitId(), pathId));
}

void Game::castUnitSpell(const Unit *unit, int pathId, int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), row, col, unit->getUnitId(), pathId));
}

void Game::castUnitSpell(const Unit *unit, int pathId, int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, unit->getUnitId(), pathId));
}

void Game::castUnitSpell(const Unit *unit, const Path *path, const Cell *cell, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), cell->getRow(), cell->getCol(), unit->getUnitId(), path->getId()));
}

void Game::castUnitSpell(const Unit *unit, const Path *path, const Cell *cell, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unit->getUnitId(), path->getId()));
}

void Game::castUnitSpell(const Unit *unit, const Path *path, int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), row, col, unit->getUnitId(), path->getId()));
}

void Game::castUnitSpell(const Unit *unit, const Path *path, int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, unit->getUnitId(), path->getId()));
}

//--------NOT-IN-DOC---------
void Game::castUnitSpell(int unitId, int pathId, int index, int spellId) {
    const Cell *cell = map_.getPaths()[pathId]->getCells()[index];
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int index, const Spell* spell) {
    castUnitSpell(unitId, pathId, index, spell->getTypeId());
}
//------NOT-IN-DOC-DONE------

void Game::castAreaSpell(const Cell *center, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), center->getRow(), center->getCol(), 0, 0));
}

void Game::castAreaSpell(const Cell *center, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, center->getRow(), center->getCol(), 0, 0));
}

void Game::castAreaSpell(int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->getTypeId(), row, col, 0, 0));
}

void Game::castAreaSpell(int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, 0, 0));
}


std::vector<const Unit *> Game::getAreaSpellTargets(const Cell *center, const Spell *spell) {
    return getAreaSpellTargets(center->getRow(), center->getCol(), spell);
}

std::vector<const Unit *> Game::getAreaSpellTargets(const Cell *center, int spellId) {
    return getAreaSpellTargets(center->getRow(), center->getCol(), give_spell_by_typeId(spellId));
}

std::vector<const Unit *> Game::getAreaSpellTargets(int row, int col, const Spell *spell) {
    int min_row = row - spell->getRange();
    int max_row = row + spell->getRange();
    int min_col = col - spell->getRange();
    int max_col = col + spell->getRange();
    min_row = min_row >= 0 ? min_row : 0;
    max_row = max_row <= map_.getRowNum() ? max_row : map_.getRowNum();
    min_col = min_col >= 0 ? min_col : 0;
    max_col = max_col <= map_.getColNum() ? max_col : map_.getColNum();

    std::vector<const Unit *> targets;

    for (int i = min_row; i <= max_row; i++)
        for (int j = min_col; j <= max_col; j++)
            for (const Unit *unit:map_.cell(i, j)->getUnits()) {
                int unit_player_id = unit->getPlayerId();
                if (spell->getTarget() == SELF && unit_player_id == my_id_)
                    targets.push_back(unit);
                else if (spell->getTarget() == ALLIED &&
                         (unit_player_id == my_id_ || unit_player_id == friend_id_))
                    targets.push_back(unit);
                else if (spell->getTarget() == ENEMY &&
                         (unit_player_id == first_enemy_id_ || unit_player_id == second_enemy_id_))
                    targets.push_back(unit);
            }
    return targets;
}

std::vector<const Unit *> Game::getAreaSpellTargets(int row, int col, int spellId) {
    return getAreaSpellTargets(row, col, give_spell_by_typeId(spellId));
}


int Game::getRemainingTurnsToUpgrade() {
    int turns_to_upgrade = game_constants_.getTurnsToUpgrade();
    return turns_to_upgrade - current_turn_ % turns_to_upgrade;
}

int Game::getRemainingTurnsToGetSpell() {
    int turns_to_spell = game_constants_.getTurnsToSpell();
    return turns_to_spell - current_turn_ % turns_to_spell;
}


int Game::getRangeUpgradeNumber() {
    return available_range_upgrades_;
}

int Game::getDamageUpgradeNumber() {
    return available_damage_upgrades_;
}


const Spell *Game::getReceivedSpell() {
    return received_spell_;
}


const Spell *Game::getFriendReceivedSpell() {
    return friend_received_spell_;
}


void Game::upgradeUnitRange(const Unit* unit) {
    upgradeUnitRange(unit->getUnitId());
}

void Game::upgradeUnitRange(int unitId) {
    event_queue_.push(CreateRangeUpgradeMessage(current_turn_, unitId));
}

void Game::upgradeUnitDamage(const Unit* unit) {
    upgradeUnitDamage(unit->getUnitId());
}

void Game::upgradeUnitDamage(int unitId) {
    event_queue_.push(CreateDamageUpgradeMessage(current_turn_, unitId));
}


std::vector<const BaseUnit *> Game::getAllBaseUnits() {
    return base_units_;
}


std::vector<const Spell *> Game::getAllSpells() {
    return spells_;
}


const King *Game::getKingById(int player_id) {
    return getPlayerById(player_id)->getKing();
}

const Spell *Game::getSpellById(int spell_id) {
    return spells_[spell_id];
}

const BaseUnit *Game::getBaseUnitById(int type_id) {
    return base_units_[type_id];
}

const Player *Game::getPlayerById(int player_id) {
    return &players_[player_id];
}

const Unit *Game::getUnitById(int unit_id) {
    return unit_ptr_by_Id(unit_id);
}


const GameConstants *Game::getGameConstants() {
    return &game_constants_;
}

//----------PRIVATE-----------
int Game::give_friends_id(int id_of_player) {
    if(id_of_player == my_id_)
        return friend_id_;
    else if(id_of_player == friend_id_)
        return my_id_;
    else if(id_of_player == first_enemy_id_)
        return second_enemy_id_;
    else if(id_of_player == second_enemy_id_)
        return first_enemy_id_;

    assert(0);
}

int Game::give_an_enemy_id(int id_of_player) {
    if(id_of_player == my_id_)
        return first_enemy_id_;
    else if(id_of_player == friend_id_)
        return second_enemy_id_;
    else if(id_of_player == first_enemy_id_)
        return friend_id_;
    else if(id_of_player == second_enemy_id_)
        return my_id_;

    assert(0);
}


bool Game::is_unit_spell_(int typeId) {
    return this->give_spell_by_typeId(typeId)->getType() == SpellType ::TELE;
}

bool Game::is_player_or_friend_spell_(int playerId) {
    return my_id_ == playerId && my_id_ == friend_id_;
}

Unit *Game::unit_ptr_by_Id(int unitId) {
    for(Unit* unit_ptr : this->ALLunits_){
        if(unit_ptr->getUnitId() == unitId){
            return unit_ptr;
        }
    }

    Logger::Get(LogLevel_ERROR) << "Game::unit_ptr_by_Id:: unitId: " << unitId << " not found..." << std::endl;
    assert(0);
}

const CastSpell *Game::cast_spell_ptr_by_Id(int castSpellId) {
    for(const CastSpell * cSpell_ptr: cast_spell_){
        if (cSpell_ptr->id_ == castSpellId)
            return cSpell_ptr;
    }

    Logger::Get(LogLevel_ERROR) << "Game::cast_spell_ptr_by_Id:: Wrong castSpellId" << std::endl;
    assert(0);
}

const Path *Game::path_ptr_by_pathId(int pathId) {
    for (const Path *path_ptr: this->map_.getPaths()) {
        if (path_ptr->getId() == pathId)
            return path_ptr;
    }

    Logger::Get(LogLevel_ERROR) << "Game::path_ptr_by_pathId:: Wrong pathId" << std::endl;
    assert(0);
}


const Spell *Game::give_spell_by_typeId(int spell_id) const {
    for(const Spell *_spell: this->spells_){
        if(_spell->getTypeId() == spell_id){
            return _spell;
        }
    }

    assert(0);
}


int Game::getTurnTimeout() {
    return game_constants_.getTurnTimeout();
}

int Game::getPickTimeout() {
    return game_constants_.getPickTimeout();
}


