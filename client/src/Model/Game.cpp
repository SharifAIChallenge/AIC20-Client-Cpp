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
    for(const Spell * _my_spell:obj.my_spells_){
        this->my_spells_.push_back(
                this->spell(_my_spell->typeId())
        );
    }
    for(const Spell * _friend_spell:obj.friend_spells_){
        this->friend_spells_.push_back(
                this->spell(_friend_spell->typeId())
        );
    }

//    if (obj.received_spell_ != nullptr)
//        this->received_spell_ = this->spells_[obj.received_spell_->typeId()];
//    else
//        this->received_spell_ = nullptr;
//
//    if (obj.friend_received_spell_ != nullptr)
//        this->friend_received_spell_ = this->spells_[obj.friend_received_spell_->typeId()];
//    else
//        this->friend_received_spell_ = nullptr;


    for(int i = 0; i < 4; i++) {
        this->players_[i].player_id_ = obj.players_[i].player_id_;
        this->players_[i].ap_ = obj.players_[i].ap_;
        this->players_[i].king_ = new King(*(obj.players_[i].king_));//The center_ pointer is still on the old one

        this->players_[i].king_->center_ = this->map_.cell(
                obj.players_[i].king_->center_->getRow(),
                obj.players_[i].king_->center_->getCol()
        );

        for(const Spell *_spell: obj.players_[i].spells_){
            this->players_[i].spells_.push_back(
                    new Spell(*_spell)
            );
        }

        for(const BaseUnit *_bUnit_deck: obj.players_[i].deck_) {
            this->players_[i].deck_.push_back(this->base_units_[_bUnit_deck->typeId()]);
        }

        for(const BaseUnit *_bUnit_hand: obj.players_[i].hand_) {
            this->players_[i].hand_.push_back(this->base_units_[_bUnit_hand->typeId()]);
        }
    }

//    for(const CastAreaSpell *obj_cASpell: obj.cast_area_spell_){
//        CastAreaSpell* cast_area_spell_ptr = new CastAreaSpell();
//
//        cast_area_spell_ptr->caster_id_ = obj_cASpell->caster_id_;
//        cast_area_spell_ptr->type_ = obj_cASpell->type_;
//        cast_area_spell_ptr->id_ = obj_cASpell->id_;
//
//        cast_area_spell_ptr->center_ = this->map_.cell(
//                obj_cASpell->center_->getRow(),
//                obj_cASpell->center_->getCol()
//        );
//        cast_area_spell_ptr->remaining_turns_ = obj_cASpell->remaining_turns_;
//        cast_area_spell_ptr->was_cast_this_turn_ = obj_cASpell->was_cast_this_turn_;
//
//        for(const Unit *obj_cASpell_aUnit:obj_cASpell->affected_units_){
//            cast_area_spell_ptr->affected_units_.push_back(
//                    this->unit_ptr_by_Id(obj_cASpell_aUnit->unitId())
//            );
//        }
//
//        this->cast_area_spell_.push_back(cast_area_spell_ptr);
//        this->cast_spell_.push_back(cast_area_spell_ptr);
//    }
//
//    for(const CastUnitSpell *obj_cUSpell: obj.cast_unit_spell_){
//        CastUnitSpell* cast_unit_spell_ptr = new CastUnitSpell();
//
//        cast_unit_spell_ptr->caster_id_ = obj_cUSpell->caster_id_;
//        cast_unit_spell_ptr->type_ = obj_cUSpell->type_;
//        cast_unit_spell_ptr->id_ = obj_cUSpell->id_;
//
//        cast_unit_spell_ptr->unit_id_ = obj_cUSpell->unit_id_;
//        cast_unit_spell_ptr->path_id_ = obj_cUSpell->path_id_;
//
//        cast_unit_spell_ptr->target_cell_ = this->map_.cell(
//                obj_cUSpell->target_cell_->getRow(),
//                obj_cUSpell->target_cell_->getCol()
//        );
//
//        this->cast_unit_spell_.push_back(cast_unit_spell_ptr);
//        this->cast_spell_.push_back(cast_unit_spell_ptr);
//    }

//    for (int player_id = 0; player_id < 4; player_id++) {
//        for(const Path *path_: obj.paths_from_player_[player_id]){
//            this->paths_from_player_[player_id].push_back(
//                    this->path_ptr_by_pathId(path_->pathId()));
//        }
//    }
//
//    for (int player_id = 0; player_id < 4; player_id++) {
//        this->path_to_friend_[player_id] = this->path_ptr_by_pathId(
//                obj.path_to_friend_[player_id]->pathId()
//        );
//    }


}

Game::~Game() {
    //todo complete
}

void Game::initPlayerData() {

    //Parse player::paths_from_player_ TODO

    //Parse player::path_to_friend TODO

    for (int player_id = 0; player_id < 4; player_id++) {
        int friend_id_ = getFriend()->player_id_;

        for (const Path *path : map_.paths()) {
            if (path->cells()[0] == players_[player_id].king()->center() &&
                path->cells().back() != players_[friend_id_].king()->center()) {
                this->players_[player_id].paths_from_player_.push_back(
                        new Path(*path, false)
                );
            } else if (path->cells().back() == players_[player_id].king()->center() &&
                     path->cells()[0] != players_[friend_id_].king()->center()) {
                this->players_[player_id].paths_from_player_.push_back(
                        new Path(*path, true)
                );
            } else if (path->cells()[0] == players_[player_id].king()->center() &&
                       path->cells().back() == players_[friend_id_].king()->center()){
                this->players_[player_id].path_to_friend = new Path(*path, false);
            } else if (path->cells().back() == players_[player_id].king()->center() &&
                       path->cells()[0] == players_[friend_id_].king()->center()) {
                this->players_[player_id].path_to_friend = new Path(*path, true);
            }
        }
    }
}

int Game::currentTurn() {
    return current_turn_;
}

void Game::chooseDeckById(std::vector<int> type_ids) {
    event_queue_.push(CreatePickMessage(type_ids));
}

void Game::chooseDeck(std::vector<BaseUnit *> baseUnits) {
    std::vector<int> type_ids;
    for(BaseUnit* _baseU:baseUnits){
        type_ids.push_back(_baseU->typeId());
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


const Cell *Game::getPlayerPosition(int player_id) {
    return players_[player_id].king()->center();
}

//std::vector<const Path *> Game::getPathsFromPlayer(int player_id) {
//    return paths_from_player_[player_id];
//}
//
//const Path *Game::getPathToFriend(int player_id) {
//    return path_to_friend_[player_id];
//}

int Game::getMapRowNum() {
    return map_.rowNum();
}

int Game::getMapColNum() {
    return map_.colNum();
}

std::vector<const Path *> Game::getPathsCrossingCell(Cell cell) {
    std::vector<const Path *> cross;
    for (const Path *path : map_.paths())
        for (const Cell *c : path->cells())
            if (*c == cell) {
                cross.push_back(path);
                break;
            }

    return cross;
}


std::vector<const Path *> Game::getPathsCrossingCell(int row, int col) {
    std::vector<const Path *> cross;
    for (const Path *path : map_.paths())
        for (const Cell *c : path->cells())
            if (c->getRow() == row && c->getCol() == col) {
                cross.push_back(path);
                break;
            }

    return cross;
}

std::vector<const Unit *> Game::getPlayerUnits(int player_id) {
    std::vector<const Unit *> units;
    for (const Unit *unit : map_.units())
        if (unit->playerId() == player_id)
            units.push_back(unit);
    return units;
}

std::vector<const Unit *> Game::getCellUnits(Cell cell) {
    std::vector<const Unit *> units;

    for (const Unit *unit : map_.units())
        if (*unit->cell() == cell)
            units.push_back(unit);

    return units;
}

std::vector<const Unit *> Game::getCellUnits(int row, int col) {
    std::vector<const Unit *> units;

    for (const Unit *unit : map_.units())
        if (unit->cell()->getRow() == row &&
            unit->cell()->getCol() == col)
            units.push_back(unit);

    return units;
}

//TODO add the friend path too!
const Path *Game::getShortestPathToCell(const Player* from_player, Cell cell) {
    std::vector<const Path *> paths = from_player->getPathsFromPlayer();
    size_t min = 0x7fffffff;
    const Path *shortest = nullptr;

    for (const Path *path : paths) {
        for (size_t i = 0; i < path->cells().size(); i++)
            if (*path->cells()[i] == cell) {
                if (i < min) {
                    min = i;
                    shortest = path;
                } else
                    continue;
            }
    }

    return shortest;
}
//TODO add the friend path too!
const Path *Game::getShortestPathToCell(const Player* from_player, int row, int col) {
    std::vector<const Path *> paths = from_player->getPathsFromPlayer();
    size_t min = 0x7fffffff;
    const Path *shortest = nullptr;

    for (const Path *path : paths) {
        for (size_t i = 0; i < path->cells().size(); i++)
            if (path->cells()[i]->getRow() == row &&
                path->cells()[i]->getCol() == col) {
                if (i < min) {
                    min = i;
                    shortest = path;
                } else
                    continue;
            }
    }

    return shortest;
}

int Game::getMaxAp() {
    return game_constants_.maxAp();
}

int Game::getRemainingAp() {
    return players_[my_id_].ap();
}

std::vector<const BaseUnit *> Game::getHand() {
    return players_[my_id_].hand();
}

std::vector<const BaseUnit *> Game::getDeck() {
    return players_[my_id_].deck();
}

void Game::putUnit(int typeId, int pathId) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, typeId, pathId));
}

void Game::putUnit(const BaseUnit* baseUnit, int pathId) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, baseUnit->typeId(), pathId));
}

void Game::putUnit(int typeId, const Path* path) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, typeId, path->pathId()));
}

void Game::putUnit(const BaseUnit* baseUnit, const Path* path) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, baseUnit->typeId(), path->pathId()));
}

int Game::getCurrentTurn() {
    return currentTurn();
}

int Game::getMaxTurns() {
    return game_constants_.maxTurns();
}

int Game::getPickTimeout() {
    return game_constants_.pickTimeout();
}

int Game::getTurnTimeout() {
    return game_constants_.turnTimeout();
}

int Game::getRemainingTime() {
    int duration = getTime();

    if (current_turn_ == 0)
        return getPickTimeout() - (duration - start_time_);
    else
        return getTurnTimeout() - (duration - start_time_);
}

int Game::getPlayerHp(int player_id) {
    return players_[player_id].king()->hp();
}

void Game::castUnitSpell(int unitId, int pathId, const Cell *cell, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->typeId(), cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, const Cell *cell, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->typeId(), row, col, unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, unitId, pathId));
}

//--------NOT-IN-DOC---------
void Game::castUnitSpell(int unitId, int pathId, int index, int spellId) {
    const Cell *cell = map_.paths()[pathId]->cells()[index];
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int index, Spell spell) {
    castUnitSpell(unitId, pathId, index, spell.typeId());
}
//------NOT-IN-DOC-DONE------

void Game::castAreaSpell(const Cell *center, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->typeId(), center->getRow(), center->getCol(), 0, 0));
}

void Game::castAreaSpell(const Cell *center, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, center->getRow(), center->getCol(), 0, 0));
}

void Game::castAreaSpell(int row, int col, const Spell *spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell->typeId(), row, col, 0, 0));
}

void Game::castAreaSpell(int row, int col, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, row, col, 0, 0));
}

std::vector<const Unit *> Game::getAreaSpellTargets(const Cell *center, const Spell *spell) {
    return getAreaSpellTargets(center->getRow(), center->getCol(), spell);
}

std::vector<const Unit *> Game::getAreaSpellTargets(const Cell *center, int spellId) {
    return getAreaSpellTargets(center->getRow(), center->getCol(), spell(spellId));
}

std::vector<const Unit *> Game::getAreaSpellTargets(int row, int col, const Spell *spell) {
    int min_row = row - spell->range();
    int max_row = row + spell->range();
    int min_col = col - spell->range();
    int max_col = col + spell->range();
    min_row = min_row >= 0 ? min_row : 0;
    max_row = max_row <= map_.rowNum() ? max_row : map_.rowNum();
    min_col = min_col >= 0 ? min_col : 0;
    max_col = max_col <= map_.colNum() ? max_col : map_.colNum();

    std::vector<const Unit *> targets;

    for (int i = min_row; i <= max_row; i++)
        for (int j = min_col; j <= max_col; j++)
            for (const Unit *unit:map_.cell(i, j)->units()) {
                int unit_player_id = unit->playerId();
                if (spell->target() == SELF && unit_player_id == my_id_)
                    targets.push_back(unit);
                else if (spell->target() == ALLIED &&
                         (unit_player_id == my_id_ || unit_player_id == friend_id_))
                    targets.push_back(unit);
                else if (spell->target() == ENEMY &&
                         (unit_player_id == first_enemy_id_ || unit_player_id == second_enemy_id_))
                    targets.push_back(unit);
            }
    return targets;
}

std::vector<const Unit *> Game::getAreaSpellTargets(int row, int col, int spellId) {
    return getAreaSpellTargets(row, col, spell(spellId));
}

int Game::getRemainingTurnsToUpgrade() {
    int turns_to_upgrade = game_constants_.turnsToUpgrade();
    return turns_to_upgrade - current_turn_ % turns_to_upgrade;
}

int Game::getRemainingTurnsToGetSpell() {
    int turns_to_spell = game_constants_.turnsToSpell();
    return turns_to_spell - current_turn_ % turns_to_spell;
}
//TODO write an overload

////TODO complete this
//const CastAreaSpell *Game::getCastAreaSpell(int player_id) {
////    return cast_area_spell_[player_id]; TODO for loop here
//
//}
//
//const CastUnitSpell *Game::getCastUnitSpell(int player_id) {
////    return cast_unit_spell_[player_id]; TODO for loop here
//
//}
//
//std::vector<Spell *> Game::getCastSpellsOnUnit(Unit unit) {
//    return std::vector<Spell *>(); //todo
//}
//
//std::vector<Spell *> Game::getCastSpellsOnUnit(int unitId) {
//    return std::vector<Spell *>(); //todo
//}

int Game::getRangeUpgradeNumber() {
    return available_range_upgrades_;
}

int Game::getDamageUpgradeNumber() {
    return available_damage_upgrades_;
}

//std::vector<const Spell *> Game::getSpellsList() {
//    return my_spells_;
//}

//std::map<const Spell *, int> Game::getSpells() {
//    return my_spells_map_;
//}

const Spell *Game::getReceivedSpell() {
    return received_spell_;
}

const Spell *Game::getFriendReceivedSpell() {
    return friend_received_spell_;
}

void Game::upgradeUnitRange(const Unit* unit) {
    upgradeUnitRange(unit->unitId());
}

void Game::upgradeUnitRange(int unitId) {
    event_queue_.push(CreateRangeUpgradeMessage(current_turn_, unitId));
}

void Game::upgradeUnitDamage(const Unit* unit) {
    upgradeUnitDamage(unit->unitId());
}

void Game::upgradeUnitDamage(int unitId) {
    event_queue_.push(CreateDamageUpgradeMessage(current_turn_, unitId));
}

std::vector<const Unit *> Game::getPlayerDuplicateUnits(int player_id) {
    std::vector<const Unit *> duplicates;
    for (const Unit *unit : map_.units())
        if (unit->playerId() == player_id && unit->isDuplicate())
            duplicates.push_back(unit);
    return duplicates;
}

std::vector<const Unit *> Game::getPlayerHastedUnits(int player_id) {
    std::vector<const Unit *> haste;
    for (const Unit *unit : map_.units())
        if (unit->playerId() == player_id && unit->isHasted())
            haste.push_back(unit);
    return haste;
}

std::vector<const Unit *> Game::getPlayerPlayedUnits(int player_id) { // todo is correct?
    std::vector<const Unit *> played;
    for (const Unit *unit : map_.units())
        if (unit->playerId() == player_id && unit->wasPlayedThisTurn())
            played.push_back(unit);
    return played;
}

const King *Game::getKingById(int player_id) {
    return players_[player_id].king();
}

const Spell *Game::spell(int spell_id) const {
    return spells_[spell_id];
}

bool Game::is_unit_spell_(int typeId) {
    return this->spell(typeId)->type() == SpellType ::TELE;
}

bool Game::is_player_or_friend_spell_(int playerId) {
    return my_id_ == playerId && my_id_ == friend_id_;
}

const Unit *Game::unit_ptr_by_Id(int unitId) {

    for(const Unit* unit_ptr : map_.units()){
        if(unit_ptr->unitId() == unitId){
            return unit_ptr;
        }
    }

    Logger::Get(LogLevel_ERROR) << "Game::unit_ptr_by_Id:: unitTd not found..." << std::endl;
    assert(0);
}

const Unit *Game::getUnitTarget(Unit unit) {
    int target_id = unit.target_id_;
    if (target_id < 4)
        return nullptr;
    return unit_ptr_by_Id(target_id);
}

const Unit *Game::getUnitTarget(int unit_id) {
    return getUnitTarget(*unit_ptr_by_Id(unit_id));
}

const Cell * Game::getUnitTargetCell(Unit unit) {
    return unit.targetCell();
}

const Cell * Game::getUnitTargetCell(int unit_id) {
    return unit_ptr_by_Id(unit_id)->targetCell();
}

const Unit *Game::getKingTarget(int player_id) {
    int target_id = getKingById(player_id)->target_id_;
    if (target_id < 4)
        return nullptr;
    return unit_ptr_by_Id(target_id);
}

const Cell * Game::getKingTargetCell(int player_id) {
    const Unit *target = getKingTarget(player_id);
    if (target)
        return getKingTarget(player_id)->cell();
    return nullptr;
}

int Game::getKingUnitIsAttackingTo(Unit unit) {
    int target_id = unit.target_id_;
    if (target_id < 4 && target_id >= 0)
        return target_id;
    return -1;
}

int Game::getKingUnitIsAttackingTo(int unit_id) {
    return getKingUnitIsAttackingTo(*unit_ptr_by_Id(unit_id));
}

std::vector<const BaseUnit *> Game::getAllBaseUnits() {
    return base_units_;
}

std::vector<const Spell *> Game::getAllSpells() {
    return spells_;
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

const std::vector<const Unit *> Game::getPlayerDiedUnits(int player_id) {
    std::vector<const Unit *> units;
    for (const Unit *unit : map_.diedUnits())
        if (unit->playerId() == player_id)
            units.push_back(unit);
    return units;
}

bool Game::hasPlayerUsedRangeUpgrade(int player_id) {
    for(const Unit *unit : getPlayerUnits(player_id))
        if (unit->wasRangeUpgraded())
            return true;
    return false;
}

bool Game::hasPlayerUsedDamageUpgrade(int player_id) {
    for(const Unit *unit : getPlayerUnits(player_id))
        if (unit->wasDamageUpgraded())
            return true;
    return false;
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
    for (const Path *path_ptr: this->map_.paths()) {
        if (path_ptr->pathId() == pathId)
            return path_ptr;
    }

    Logger::Get(LogLevel_ERROR) << "Game::path_ptr_by_pathId:: Wrong pathId" << std::endl;
    assert(0);
}

const Map *Game::getMap() {
    return &map_;

}

const GameConstants *Game::getGameConstants() {
    return &game_constants_;
}



