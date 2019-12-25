#ifndef AIC20_CLIENT_CPP_WORLD_H
#define AIC20_CLIENT_CPP_WORLD_H

#include <vector>

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


    virtual void chooseDeck(std::vector <int *> typeIds) = 0;

    // todo void chooseDeck(std::vector<Enum *> typeIds)

    virtual int getMyId() = 0;

    virtual int getFriendId() = 0;

    virtual Cell getPLayerPosition(int playerId) = 0;

    virtual std::vector <Path *> getPathsFromPlayer(int playerID) = 0;

    virtual Path getPathToFriend(int playerId) = 0;

    virtual int getMapHeight() = 0;

    virtual int getMapWidth() = 0;

    virtual std::vector <Path *> getPathsCrossingCell(Cell cell) = 0;

    virtual std::vector <Unit *> getPlayerUnits(int playerId) = 0;

    virtual std::vector <Unit *> getCellUnits(Cell cell) = 0;

    virtual Path getShortestPathToCell(int fromPlayerId, Cell cell) = 0;

    virtual int getMaxAp() = 0;

    virtual int getRemainingAp() = 0;

    virtual std::vector <Unit *> getHand() = 0;

    virtual std::vector <Unit *> getDeck() = 0;

    virtual void playUnit(int typeId, int pathId) = 0;

    virtual int getCurrentTurn() = 0;

    virtual int getMaxTurns() = 0;

    virtual int getPickTimeout() = 0;

    virtual int getTurnTimeout() = 0;

    virtual int getRemainingTime() = 0;

    virtual int getPlayerHp(int playerId) = 0;

    virtual void castUnitSpell(int unitId, int pathId, int index, int spellId) = 0;

    virtual void castUnitSpell(int unitId, int pathId, int index, Spell spell) = 0;

    virtual void castAreaSpell(Cell center, int spellId) = 0;

    virtual void castAreaSpell(Cell center, Spell spell) = 0;

    virtual std::vector <Unit *> getAreaSpellTargets(Cell center, Spell spell) = 0;

    virtual std::vector <Unit *> getAreaSpellTargets(Cell center, int SpellId) = 0;

    virtual int getRemainingTurnsToUpgrade() = 0;

    virtual int getRemainingTurnsToGetSpell() = 0;

    virtual CastAreaSpell getCastAreaSpell(int playerId) = 0;

    virtual CastUnitSpell getCastUnitSpell(int playerId) = 0;

    virtual std::vector <CastAreaSpell *> getActiveSpellsOnCell(Cell cell) = 0;

    virtual int getUpgradeTokenNumber() = 0;

    virtual std::vector <Spell *> getSpells() = 0;

    virtual Spell getRecievedSpell() = 0;

    virtual Spell getFriendRecievedSpell() = 0;
};


#endif //AIC20_CLIENT_CPP_WORLD_H
