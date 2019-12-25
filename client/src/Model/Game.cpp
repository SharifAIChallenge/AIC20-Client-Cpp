#include "Game.h"

Game::Game(EventQueue &event_queue): _event_queue(event_queue){

}

void Game::initData() {

}

void Game::chooseDeck(std::vector<int *> typeIds) {

}

int Game::currentTurn() {
    return _current_turn;
}

int Game::getMyId() {
    return 0;
}

int Game::getFriendId() {
    return 0;
}

Cell Game::getPLayerPosition(int playerId) {
    return Cell();
}

std::vector<Path *> Game::getPathsFromPlayer(int playerID) {
    return std::vector<Path *>();
}

Path Game::getPathToFriend(int playerId) {
    return Path();
}

int Game::getMapHeight() {
    return 0;
}

int Game::getMapWidth() {
    return 0;
}

std::vector<Path *> Game::getPathsCrossingCell(Cell cell) {
    return std::vector<Path *>();
}

std::vector<Unit *> Game::getPlayerUnits(int playerId) {
    return std::vector<Unit *>();
}

std::vector<Unit *> Game::getCellUnits(Cell cell) {
    return std::vector<Unit *>();
}

Path Game::getShortestPathToCell(int fromPlayerId, Cell cell) {
    return Path();
}

int Game::getMaxAp() {
    return 0;
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

void Game::playUnit(int typeId, int pathId) {

}

int Game::getCurrentTurn() {
    return 0;
}

int Game::getMaxTurns() {
    return 0;
}

int Game::getPickTimeout() {
    return 0;
}

int Game::getTurnTimeout() {
    return 0;
}

int Game::getRemainingTime() {
    return 0;
}

int Game::getPlayerHp(int playerId) {
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

std::vector<Unit *> Game::getAreaSpellTargets(Cell center, int SpellId) {
    return std::vector<Unit *>();
}

int Game::getRemainingTurnsToUpgrade() {
    return 0;
}

int Game::getRemainingTurnsToGetSpell() {
    return 0;
}

CastAreaSpell Game::getCastAreaSpell(int playerId) {
    return CastAreaSpell();
}

CastUnitSpell Game::getCastUnitSpell(int playerId) {
    return CastUnitSpell();
}

std::vector<CastAreaSpell *> Game::getActiveSpellsOnCell(Cell cell) {
    return std::vector<CastAreaSpell *>();
}

int Game::getUpgradeTokenNumber() {
    return 0;
}

std::vector<Spell *> Game::getSpells() {
    return std::vector<Spell *>();
}

Spell Game::getRecievedSpell() {
    return Spell();
}

Spell Game::getFriendRecievedSpell() {
    return Spell();
}
