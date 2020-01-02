#ifndef AIC20_CLIENT_CPP_WORLD_H
#define AIC20_CLIENT_CPP_WORLD_H

#include <vector>
#include <map>

#include "Cell.h"
#include "Path.h"
#include "Unit.h"
#include "AreaSpell.h"
#include "UnitSpell.h"
#include "CastAreaSpell.h"
#include "CastUnitSpell.h"

class World {
public:
    World() = default;

    ~World() = default;


    virtual void chooseDeck(std::vector<int *> typeIds) = 0;

    // todo void chooseDeck(std::vector<Enum *> typeIds)

    virtual int getMyId() = 0;

    virtual int getFriendId() = 0;

    virtual int getFirstEnemyId() = 0;

    virtual int getSecondEnemyId() = 0;

    virtual const Cell *getPlayerPosition(int player_id) = 0;

    virtual std::vector<Path *> getPathsFromPlayer(int player_id) = 0;

    virtual const Path *getPathToFriend(int player_id) = 0;

    virtual int getMapRowNum() = 0;

    virtual int getMapColNum() = 0;

    virtual std::vector<Path *> getPathsCrossingCell(Cell cell) = 0;

    virtual std::vector<Unit *> getPlayerUnits(int player_id) = 0;

    virtual std::vector<Unit *> getCellUnits(Cell cell) = 0;

    virtual const Path *getShortestPathToCell(int from_player, Cell cell) = 0;

    virtual int getMaxAp() = 0;

    virtual int getRemainingAp() = 0;

    virtual std::vector<BaseUnit *> getHand() = 0;

    virtual std::vector<BaseUnit *> getDeck() = 0;

    virtual void putUnit(int typeId, int pathId) = 0;

    virtual int getCurrentTurn() = 0;

    virtual int getMaxTurns() = 0;

    virtual int getPickTimeout() = 0;

    virtual int getTurnTimeout() = 0;

    virtual int getRemainingTime() = 0;

    virtual int getPlayerHp(int player_id) = 0;

    virtual void castUnitSpell(int unitId, int pathId, int index, int spellId) = 0;

    virtual void castUnitSpell(int unitId, int pathId, int index, Spell spell) = 0;

    virtual void castAreaSpell(Cell center, int spellId) = 0;

    virtual void castAreaSpell(Cell center, Spell spell) = 0;

    virtual std::vector<Unit *> getAreaSpellTargets(Cell center, Spell spell) = 0;

    virtual std::vector<Unit *> getAreaSpellTargets(Cell center, int spellId) = 0;

    virtual std::vector<Unit *> getAreaSpellTargets(int row, int col, Spell spell) = 0;

    virtual std::vector<Unit *> getAreaSpellTargets(int row, int col, int spellId) = 0;

    virtual int getRemainingTurnsToUpgrade() = 0;

    virtual int getRemainingTurnsToGetSpell() = 0;

    virtual const CastAreaSpell * getCastAreaSpell(int player_id) = 0;

    virtual const CastUnitSpell * getCastUnitSpell(int player_id) = 0;

    virtual std::vector<Spell *> getCastSpellsOnUnit(Unit unit) = 0;

    virtual std::vector<Spell *> getCastSpellsOnUnit(int unitId) = 0;

    virtual int getRangeUpgradeNumber() = 0;

    virtual int getDamageUpgradeNumber() = 0;

    virtual std::vector<Spell *> getSpellsList() = 0;

    virtual std::map<Spell *, int> getSpells() = 0; //todo remove??


    virtual const Spell *getReceivedSpell() = 0;

    virtual const Spell *getFriendReceivedSpell() = 0;


    virtual void upgradeUnitRange(Unit unit) = 0;

    virtual void upgradeUnitRange(int unitId) = 0;

    virtual void upgradeUnitDamage(Unit unit) = 0;

    virtual void upgradeUnitDamage(int unitId) = 0;


    virtual std::vector<Unit *> getPlayerDuplicateUnits(int player_id) = 0;

    virtual std::vector<Unit *> getPlayerHastedUnits(int player_id) = 0;


    virtual std::vector<Unit *> getPlayerPlayedUnits(int player_id) = 0;
};


#endif //AIC20_CLIENT_CPP_WORLD_H
