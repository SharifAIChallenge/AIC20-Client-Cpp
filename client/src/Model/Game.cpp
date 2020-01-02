#include "Game.h"

#include "Utility/Utility.h"

Game::Game(EventQueue &event_queue) : _event_queue(event_queue) {

}

void Game::initData() {

}

void Game::chooseDeck(std::vector<int *> typeIds) {

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

Cell *Game::getPlayerPosition(int player_id) {
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

Path *Game::getPathToFriend(int player_id) {
    for (Path *path : map_.paths())
        if (path->cells()[0] == players_[player_id].king().center() &&
            path->cells().back() == players_[friend_id_].king().center())
            return path;
}

int Game::getMapRowNum() {
    return map_.row_num();
}

int Game::getMapColNum() {
    return map_.col_num();
}

std::vector<Path *> Game::getPathsCrossingCell(Cell cell) {
    return std::vector<Path *>();
}

std::vector<Unit *> Game::getPlayerUnits(int player_id) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getCellUnits(Cell cell) {
    return std::vector<Unit *>();
}

Path *Game::getShortestPathToCell(int from_player, Cell cell) {
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

}

void Game::castUnitSpell(int unitId, int pathId, int index, Spell spell) {

}

void Game::castAreaSpell(Cell center, int spellId) {

}

void Game::castAreaSpell(Cell center, Spell spell) {

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

CastAreaSpell Game::getCastAreaSpell(int player_id) {
    return CastAreaSpell();
}

CastUnitSpell Game::getCastUnitSpell(int player_id) {
    return CastUnitSpell();
}

std::vector<Spell *> Game::getCastSpellsOnUnit(Unit unit) {
    return std::vector<Spell *>();
}

std::vector<Spell *> Game::getCastSpellsOnUnit(int unitId) {
    return std::vector<Spell *>();
}

int Game::getRangeUpgradeNumber() {
    return 0;
}

int Game::getDamageUpgradeNumber() {
    return 0;
}

std::vector<Spell *> Game::getSpellsList() {
    return std::vector<Spell *>();
}

std::map<Spell *, int> Game::getSpells() {
    return std::map<Spell *, int>();
}

Spell Game::getReceivedSpell() {
    return Spell();
}

Spell Game::getFriendReceivedSpell() {
    return Spell();
}

void Game::upgradeUnitRange(Unit unit) {

}

void Game::upgradeUnitRange(int unitId) {

}

void Game::upgradeUnitDamage(Unit unit) {

}

void Game::upgradeUnitDamage(int unitId) {

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
