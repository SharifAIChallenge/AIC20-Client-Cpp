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


    void chooseDeck(std::vector <int *> typeIds);

    // todo void chooseDeck(std::vector<Enum *> typeIds)

    int getMyId();

    int getFriendId();

    Cell getPLayerPosition(int playerId);

    std::vector <Path *> getPathsFromPlayer(int playerID);

    Path getPathToFriend(int playerId);

    int getMapHeight();

    int getMapWidth();

    std::vector <Path *> getPathsCrossingCell(Cell cell);

    std::vector <Unit *> getPlayerUnits(int playerId);

    std::vector <Unit *> getCellUnits(Cell cell);

    Path getShortestPathToCell(int fromPlayerId, Cell cell);

    int getMaxAp();

    int getRemainingAp();

    std::vector <Unit *> getHand();

    std::vector <Unit *> getDeck();

    void playUnit(int typeId, int pathId);

    int getCurrentTurn();

    int getMaxTurns();

    int getPickTimeout();

    int getTurnTimeout();

    int getRemainingTime();

    int getPlayerHp(int playerId);

    void castUnitSpell(int unitId, int pathId, int index, int spellId);

    void castUnitSpell(int unitId, int pathId, int index, Spell spell);

    void castAreaSpell(Cell center, int spellId);

    void castAreaSpell(Cell center, Spell spell);

    std::vector <Unit *> getAreaSpellTargets(Cell center, Spell spell);

    std::vector <Unit *> getAreaSpellTargets(Cell center, int SpellId);

    int getRemainingTurnsToUpgrade();

    int getRemainingTurnsToGetSpell();

    CastAreaSpell getCastAreaSpell(int playerId);

    CastUnitSpell getCastUnitSpell(int playerId);

    std::vector <CastAreaSpell *> getActiveSpellsOnCell(Cell cell);

    int getUpgradeTokenNumber();

    std::vector <Spell *> getSpells();

    Spell getRecievedSpell();

    Spell getFriendRecievedSpell();
};


#endif //AIC20_CLIENT_CPP_WORLD_H
