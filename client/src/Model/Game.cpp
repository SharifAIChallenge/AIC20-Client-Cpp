#include <Core/Message/Create/CreateCastSpellMessage.h>
#include <Core/Message/Create/CreateRangeUpgradeMessage.h>
#include "Game.h"

#include "Utility/Utility.h"
#include "Core/Message/Create/CreatePutUnitMessage.h"
#include "Core/Message/Create/CreateCastSpellMessage.h"
#include "Core/Message/Create/CreatePickMessage.h"
#include "Core/Message/Create/CreateRangeUpgradeMessage.h"
#include "Core/Message/Create/CreateDamageUpgradeMessage.h"

Game::Game(EventQueue &event_queue) : event_queue_(event_queue) {

}

void Game::initData() {

}

void Game::chooseDeck(std::vector<int *> typeIds) {
    //todo
}

int Game::getMyId() {
    return my_id_;
}

int Game::getFriendId() {
    return friend_id_;
}

int Game::getFirstEnemyId() {
    return first_enemy_id_;
}

int Game::getSecondEnemyId() {
    return second_enemy_id_;
}

const Cell *Game::getPlayerPosition(int player_id) {
    return players_[player_id].king().center();
}

std::vector<Path *> Game::getPathsFromPlayer(int player_id) { //todo store it
    std::vector<Path *> cross;
    for (Path *path : map_.paths())
        if (path->cells()[0] == players_[player_id].king().center() &&
            path->cells().back() != players_[friend_id_].king().center())
            cross.push_back(path);

    return cross;
}

const Path *Game::getPathToFriend(int player_id) {
    for (Path *path : map_.paths())
        if (path->cells()[0] == players_[player_id].king().center() &&
            path->cells().back() == players_[friend_id_].king().center())
            return path;

    return nullptr;
}

int Game::getMapRowNum() {
    return map_.row_num();
}

int Game::getMapColNum() {
    return map_.col_num();
}

std::vector<Path *> Game::getPathsCrossingCell(Cell cell) {
    std::vector<Path *> cross;
    for (Path *path : map_.paths())
        for (Cell *c : path->cells())
            if (*c == cell) {
                cross.push_back(path);
                break;
            }

    return cross;
}

std::vector<Unit *> Game::getPlayerUnits(int player_id) {
    return player_units_[player_id];
}

std::vector<Unit *> Game::getCellUnits(Cell cell) {
    std::vector<Unit *> units;

    for (int i = 0; i < 4; i++)
        for (Unit *unit : player_units_[i])
            if (*unit->cell() == cell)
                units.push_back(unit);

    return units;
}

const Path *Game::getShortestPathToCell(int from_player, Cell cell) {
    std::vector<Path *> paths = getPathsFromPlayer(from_player);
    int min = 0x7fffffff;
    Path *shortest = nullptr;

    for (Path *path : paths) {
        for (int i = 0; i < path->cells().size(); i++)
            if (path->cells()[i] == &cell) {// todo ==?
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

std::vector<BaseUnit *> Game::getHand() {
    return players_[my_id_].hand();
}

std::vector<BaseUnit *> Game::getDeck() {
    return players_[my_id_].deck();
}

void Game::putUnit(int typeId, int pathId) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, typeId, pathId));
}

int Game::getCurrentTurn() {
    return current_turn_;
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
    return players_[player_id].king().hp();
}

void Game::castUnitSpell(int unitId, int pathId, int index, int spellId) {
    const Unit *unit = getUnitById(unitId);
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, unit->cell()->getRow(),
                                             unit->cell()->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int index, Spell spell) {
    const Unit *unit = getUnitById(unitId);
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell.type(), unit->cell()->getRow(),
                                             unit->cell()->getCol(), unitId, pathId));
}

void Game::castAreaSpell(Cell center, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, center.getRow(), center.getCol(), 0, 0)); //todo
}

void Game::castAreaSpell(Cell center, Spell spell) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spell.type(), center.getRow(), center.getCol(), 0, 0)); //todo
}

std::vector<Unit *> Game::getAreaSpellTargets(Cell center, Spell spell) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getAreaSpellTargets(Cell center, int spellId) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getAreaSpellTargets(int row, int col, Spell spell) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getAreaSpellTargets(int row, int col, int spellId) {
    return std::vector<Unit *>();
}

int Game::getRemainingTurnsToUpgrade() {
    int turns_to_upgrade = game_constants_.turnsToUpgrade();
    return turns_to_upgrade - current_turn_ % turns_to_upgrade;
}

int Game::getRemainingTurnsToGetSpell() {
    int turns_to_spell = game_constants_.turnsToSpell();
    return turns_to_spell - current_turn_ % turns_to_spell;
}

const CastAreaSpell *Game::getCastAreaSpell(int player_id) {
    return nullptr; //todo how to get?
}

const CastUnitSpell *Game::getCastUnitSpell(int player_id) {
    return nullptr; //todo how to get?
}

std::vector<Spell *> Game::getCastSpellsOnUnit(Unit unit) {
    return std::vector<Spell *>();
}

std::vector<Spell *> Game::getCastSpellsOnUnit(int unitId) {
    return std::vector<Spell *>();
}

int Game::getRangeUpgradeNumber() {
    return available_range_upgrades_;
}

int Game::getDamageUpgradeNumber() {
    return available_damage_upgrades_;
}

std::vector<Spell *> Game::getSpellsList() {
    return std::vector<Spell *>();
}

std::map<Spell *, int> Game::getSpells() {
    return std::map<Spell *, int>();
}

const Spell *Game::getReceivedSpell() {
    return Spell();
}

const Spell *Game::getFriendReceivedSpell() {
    return Spell();
}

void Game::upgradeUnitRange(Unit unit) {
    event_queue_.push(CreateRangeUpgradeMessage(current_turn_, unit.unitId()));
}

void Game::upgradeUnitRange(int unitId) {
    event_queue_.push(CreateRangeUpgradeMessage(current_turn_, unitId));
}

void Game::upgradeUnitDamage(Unit unit) {
    event_queue_.push(CreateDamageUpgradeMessage(current_turn_, unit.unitId()));
}

void Game::upgradeUnitDamage(int unitId) {
    event_queue_.push(CreateDamageUpgradeMessage(current_turn_, unitId));
}

std::vector<Unit *> Game::getPlayerDuplicateUnits(int player_id) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getPlayerHastedUnits(int player_id) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getPlayerPlayedUnits(int player_id) {
    return std::vector<Unit *>();
}
