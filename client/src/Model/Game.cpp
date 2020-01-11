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
    //todo remove?
}

int Game::currentTurn() {
    return current_turn_;
}

void Game::chooseDeck(std::vector<int> type_ids) {
    event_queue_.push(CreatePickMessage(type_ids));
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
    return players_[player_id].king()->center();
}

std::vector<const Path *> Game::getPathsFromPlayer(int player_id) { //todo store it
    std::vector<const Path *> cross;
    for (const Path *path : map_.paths())
        if (path->cells()[0] == players_[player_id].king()->center() &&
            path->cells().back() != players_[friend_id_].king()->center())
            cross.push_back(path);

    return cross;
}

const Path *Game::getPathToFriend(int player_id) {
    for (const Path *path : map_.paths())
        if (path->cells()[0] == players_[player_id].king()->center() &&
            path->cells().back() == players_[friend_id_].king()->center())
            return path;

    assert(0);
}

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

std::vector<const Unit *> Game::getPlayerUnits(int player_id) {
    return player_units_[player_id];
}

std::vector<const Unit *> Game::getCellUnits(Cell cell) {
    std::vector<const Unit *> units;

    for (int i = 0; i < 4; i++)
        for (const Unit *unit : player_units_[i])
            if (*unit->cell() == cell)
                units.push_back(unit);

    return units;
}

const Path *Game::getShortestPathToCell(int from_player, Cell cell) {
    std::vector<const Path *> paths = getPathsFromPlayer(from_player);
    int min = 0x7fffffff;
    const Path *shortest = nullptr;

    for (const Path *path : paths) {
        for (int i = 0; i < path->cells().size(); i++)
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

int Game::getMaxAp() {
    return game_constants_.maxAp();
}

int Game::getRemainingAp() {
    return players_[my_id_].ap();
}

std::vector<const BaseUnit *> Game::getHand() { //todo move hand to player
    std::vector<const BaseUnit *> hand;
    for (int id : hand_)
        hand.push_back(base_units_[id]);
    return hand;
}

std::vector<const BaseUnit *> Game::getDeck() { //todo move deck to player
    std::vector<const BaseUnit *> deck;
    for (int id : deck_)
        deck.push_back(base_units_[id]);
    return deck;
}

void Game::putUnit(int typeId, int pathId) {
    event_queue_.push(CreatePutUnitMessage(current_turn_, typeId, pathId));
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

void Game::castUnitSpell(int unitId, int pathId, int index, int spellId) {
    const Cell *cell = map_.paths()[pathId]->cells()[index];
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, cell->getRow(), cell->getCol(), unitId, pathId));
}

void Game::castUnitSpell(int unitId, int pathId, int index, Spell spell) {
    castUnitSpell(unitId, pathId, index, spell.typeId());
}

void Game::castAreaSpell(Cell center, int spellId) {
    event_queue_.push(CreateCastSpellMessage(current_turn_, spellId, center.getRow(), center.getCol(), 0, 0));
}

void Game::castAreaSpell(Cell center, Spell spell) {
    castAreaSpell(center, spell.typeId());
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
                targets.push_back(unit); //todo check target of spell
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

const CastAreaSpell *Game::getCastAreaSpell(int player_id) {
    return cast_area_spell_[player_id];
}

const CastUnitSpell *Game::getCastUnitSpell(int player_id) {
    return cast_unit_spell_[player_id];
}

std::vector<Spell *> Game::getCastSpellsOnUnit(Unit unit) {
    return std::vector<Spell *>(); //todo
}

std::vector<Spell *> Game::getCastSpellsOnUnit(int unitId) {
    return std::vector<Spell *>(); //todo
}

int Game::getRangeUpgradeNumber() {
    return available_range_upgrades_;
}

int Game::getDamageUpgradeNumber() {
    return available_damage_upgrades_;
}

std::vector<const Spell *> Game::getSpellsList() {
    return my_spells_;
}

std::map<Spell *, int> Game::getSpells() { //todo remove?
    return std::map<Spell *, int>();
}

const Spell *Game::getReceivedSpell() {
    return received_spell_;
}

const Spell *Game::getFriendReceivedSpell() {
    return friend_received_spell_;
}

void Game::upgradeUnitRange(Unit unit) {
    upgradeUnitRange(unit.unitId());
}

void Game::upgradeUnitRange(int unitId) {
    event_queue_.push(CreateRangeUpgradeMessage(current_turn_, unitId));
}

void Game::upgradeUnitDamage(Unit unit) {
    upgradeUnitDamage(unit.unitId());
}

void Game::upgradeUnitDamage(int unitId) {
    event_queue_.push(CreateDamageUpgradeMessage(current_turn_, unitId));
}

std::vector<const Unit *> Game::getPlayerDuplicateUnits(int player_id) {
    std::vector<const Unit *> duplicates;
    for (const Unit* unit : player_units_[player_id])
        if (unit->isDuplicate())
            duplicates.push_back(unit);
    return duplicates;
}

std::vector<const Unit *> Game::getPlayerHastedUnits(int player_id) {
    std::vector<const Unit *> haste;
    for (const Unit * unit: player_units_[player_id])
        if (unit->isHasted())
            haste.push_back(unit);
    return haste;
}

std::vector<const Unit *> Game::getPlayerPlayedUnits(int player_id) { // todo is correct?
    return player_units_[player_id];
}

const King *Game::getKingById(int player_id) {
    return players_[player_id].king();
}

const Spell *Game::spell(int spell_id) const {
    return spells_[spell_id];
}

void Game::clearUnits() {
    for (std::vector<const Unit *> &player_units : player_units_) {
        for (const Unit *unit : player_units)
            delete unit;
        player_units.clear();
    }
}
