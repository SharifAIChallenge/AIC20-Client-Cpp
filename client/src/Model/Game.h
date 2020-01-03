#ifndef AIC20_CLIENT_CPP_GAME_H
#define AIC20_CLIENT_CPP_GAME_H

#include <Core/EventQueue.h>

#include "GameConstants.h"
#include "Map.h"
#include "World.h"
#include "King.h"
#include "Player.h"

#define NUMBER_OF_PLAYERS 4

class Game : public World {
public:
    explicit Game(EventQueue &eventQueue);

    void initData();

    void chooseDeck(std::vector<int *> typeIds) override;

    int getMyId() override;

    int getFriendId() override;

    int getFirstEnemyId() override;

    int getSecondEnemyId() override;

    Cell *getPlayerPosition(int player_id) override;

    std::vector<Path *> getPathsFromPlayer(int player_id) override;

    Path *getPathToFriend(int player_id) override;

    int getMapRowNum() override;

    int getMapColNum() override;

    std::vector<Path *> getPathsCrossingCell(Cell cell) override;

    std::vector<Unit *> getPlayerUnits(int player_id) override;

    std::vector<Unit *> getCellUnits(Cell cell) override;

    Path *getShortestPathToCell(int from_player, Cell cell) override;

    int getMaxAp() override;

    int getRemainingAp() override;

    std::vector<BaseUnit *> getHand() override;

    std::vector<BaseUnit *> getDeck() override;

    void putUnit(int typeId, int pathId) override;

    int getCurrentTurn() override;

    int getMaxTurns() override;

    int getPickTimeout() override;

    int getTurnTimeout() override;

    int getRemainingTime() override;

    int getPlayerHp(int player_id) override;

    void castUnitSpell(int unitId, int pathId, int index, int spellId) override;

    void castUnitSpell(int unitId, int pathId, int index, Spell spell) override;

    void castAreaSpell(Cell center, int spellId) override;

    void castAreaSpell(Cell center, Spell spell) override;

    std::vector<Unit *> getAreaSpellTargets(Cell center, Spell spell) override;

    std::vector<Unit *> getAreaSpellTargets(Cell center, int spellId) override;

    std::vector<Unit *> getAreaSpellTargets(int row, int col, Spell spell) override;

    std::vector<Unit *> getAreaSpellTargets(int row, int col, int spellId) override;

    int getRemainingTurnsToUpgrade() override;

    int getRemainingTurnsToGetSpell() override;

    CastAreaSpell getCastAreaSpell(int player_id) override;

    CastUnitSpell getCastUnitSpell(int player_id) override;

    std::vector<Spell *> getCastSpellsOnUnit(Unit unit) override;

    std::vector<Spell *> getCastSpellsOnUnit(int unitId) override;

    int getRangeUpgradeNumber() override;

    int getDamageUpgradeNumber() override;

    std::vector<Spell *> getSpellsList() override;

    std::map<Spell *, int> getSpells() override;

    Spell getReceivedSpell() override;

    Spell getFriendReceivedSpell() override;

    void upgradeUnitRange(Unit unit) override;

    void upgradeUnitRange(int unitId) override;

    void upgradeUnitDamage(Unit unit) override;

    void upgradeUnitDamage(int unitId) override;

    std::vector<Unit *> getPlayerDuplicateUnits(int player_id) override;

    std::vector<Unit *> getPlayerHastedUnits(int player_id) override;

    std::vector<Unit *> getPlayerPlayedUnits(int player_id) override;


private:
    EventQueue &_event_queue;

    Map map_;

    GameConstants game_constants_;

    Player players_[4];

    int my_id_;
    int friend_id_;
    int first_enemy_id_;
    int second_enemy_id_;

    int current_turn_;

    int start_time_;

    std::vector<Unit *> player_units_[4];

    CastAreaSpell cast_area_spell[4];

    std::vector<BaseUnit *> base_units;

    std::vector<Spell *> spells;

    std::vector<int> deck;//TODO type (typeID)
    std::vector<int> hand;//TODO type (typeID)


    friend class InitMessage;
    friend class TurnMessage;

//    castUnitSpell           [4]CastUnitSpell
//    castSpells              []CastSpell
//
//    baseUnits     []BaseUnit
//    spells        []Spell
//    areaSpells    []AreaSpell
//    unitSpells    []UnitSpell
//
//    playerUnits             [4][]Unit
//    castAreaSpell           [4]CastAreaSpell
//    castUnitSpell           [4]CastUnitSpell
//    castSpells              []CastSpell
//    gotRangeUpgrade         bool
//    gotDamageUpgrade        bool
//    availableRangeUpgrades  int
//    availableDamageUpgrades int
//    remainingAP             int
//
//    startTime int64


};

#endif //AIC20_CLIENT_CPP_GAME_H
