#include "Game.h"

Game::Game(EventQueue &event_queue): _event_queue(event_queue){

}

void Game::initData() {

}

int Game::currentTurn() {
    return current_turn_;
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

Cell Game::getPlayerPosition(int player_id) {
    return players_[player_id].king().center();
}

std::vector<Path *> Game::getPathsFromPlayer(int player_id) {
    return std::vector<Path *>();
}

Path Game::getPathToFriend(int player_id) {
    return Path();
}

int Game::getMapHeight() {
    return map_.col_num();
}

int Game::getMapWidth() {
    return map_.row_num();
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

Path Game::getShortestPathToCell(int fromplayer_id, Cell cell) {
    return Path();
}

int Game::getMaxAp() {
    return game_constants_.maxAp();
}

int Game::getRemainingAp() {
    return 0;
}

std::vector<Unit *> Game::getHand() {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getDeck() {
    return std::vector<Unit *>();
}

void Game::putUnit(int typeId, int pathId) {

}

int Game::getCurrentTurn() {
    return 0;
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
    return 0;
}

int Game::getPlayerHp(int player_id) {
    return 0;
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
