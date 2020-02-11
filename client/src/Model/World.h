#ifndef AIC20_CLIENT_CPP_WORLD_H
#define AIC20_CLIENT_CPP_WORLD_H

#include <vector>
#include <map>

#include "Map.h"
#include "Cell.h"
#include "Path.h"
#include "Unit.h"
#include "Spell.h"
#include "King.h"
#include "CastAreaSpell.h"
#include "CastUnitSpell.h"
#include "Player.h"
#include "GameConstants.h"

class World {
public:
    World() = default;

    ~World() = default;

    virtual void chooseDeckById(std::vector<int> typeIds) = 0;
    virtual void chooseDeck(std::vector<BaseUnit *> baseUnits) = 0;

    virtual const Player *getMe() = 0;
    virtual const Player *getFriend() = 0;
    virtual const Player *getFirstEnemy() = 0;
    virtual const Player *getSecondEnemy() = 0;

    virtual const Map *getMap() = 0;

    virtual std::vector<const Path *> getPathsCrossingCell(const Cell *cell) = 0;
    virtual std::vector<const Path *> getPathsCrossingCell(int row, int col) = 0;

    virtual std::vector<const Unit *> getCellUnits(const Cell *cell) = 0;
    virtual std::vector<const Unit *> getCellUnits(int row, int col) = 0;

    /**
     * Finds the shortest path to a cell.
     * If the cell isn't on a path the output will be
     * a nullptr.
     * If the cell is on a path to friend, a path pointer
     * starting from the friends king cell will be given (
     * This way by inserting a unit on that path, the unit
     * will go on the path to friend).
     * If the cell is on the enemies path to friend the
     * function will give the shortest path.
     *
     * @return Shortest found path
     */
    virtual const Path *getShortestPathToCell(const Player* from_player, const Cell* cell) = 0;
    virtual const Path *getShortestPathToCell(const Player* from_player, int row, int col) = 0;

    virtual void putUnit(int typeId, int pathId) = 0;
    virtual void putUnit(const BaseUnit* baseUnit, int pathId) = 0;
    virtual void putUnit(int typeId, const Path* path) = 0;
    virtual void putUnit(const BaseUnit* baseUnit, const Path* path) = 0;

    virtual int getCurrentTurn() = 0;
    
    virtual int getRemainingTime() = 0;

    virtual void castUnitSpell(int unitId, int pathId, const Cell* cell, const Spell* spell) = 0;
    virtual void castUnitSpell(int unitId, int pathId, const Cell* cell, int spellId) = 0;
    virtual void castUnitSpell(int unitId, int pathId, int row, int col, const Spell* spell) = 0;
    virtual void castUnitSpell(int unitId, int pathId, int row, int col, int spellId) = 0;
//-----NOT-IN-THE-DOC------
    virtual void castUnitSpell(int unitId, int pathId, int index, int spellId) = 0;
    virtual void castUnitSpell(int unitId, int pathId, int index, const Spell*  spell) = 0;
//---NOT-IN-THE-DOC-DONE---

    virtual void castAreaSpell(const Cell* center, const Spell* spell) = 0;
    virtual void castAreaSpell(const Cell* center, int spellId) = 0;
    virtual void castAreaSpell(int row, int col, const Spell* spell) = 0;
    virtual void castAreaSpell(int row, int col, int spellId) = 0;

    virtual std::vector<const Unit *> getAreaSpellTargets(const Cell *center, const Spell *spell) = 0;
    virtual std::vector<const Unit *> getAreaSpellTargets(const Cell *center, int spellId) = 0;
    virtual std::vector<const Unit *> getAreaSpellTargets(int row, int col, const Spell *spell) = 0;
    virtual std::vector<const Unit *> getAreaSpellTargets(int row, int col, int spellId) = 0;

    virtual int getRemainingTurnsToUpgrade() = 0;
    virtual int getRemainingTurnsToGetSpell() = 0;

    virtual int getRangeUpgradeNumber() = 0;
    virtual int getDamageUpgradeNumber() = 0;

    virtual const Spell *getReceivedSpell() = 0;

    virtual const Spell *getFriendReceivedSpell() = 0;

    virtual void upgradeUnitRange(const Unit* unit) = 0;
    virtual void upgradeUnitRange(int unitId) = 0;
    virtual void upgradeUnitDamage(const Unit* unit) = 0;
    virtual void upgradeUnitDamage(int unitId) = 0;

    virtual std::vector<const BaseUnit *> getAllBaseUnits() = 0;

    virtual std::vector<const Spell *> getAllSpells() = 0;

    virtual const King *getKingById(int player_id) = 0;
    virtual const Spell *getSpellById(int spell_id) = 0;
    virtual const BaseUnit *getBaseUnitById(int type_id) = 0;
    virtual const Player *getPlayerById(int player_id) = 0;
    virtual const Unit *getUnitById(int unit_id) = 0;

    virtual const GameConstants *getGameConstants() = 0;

};


#endif //AIC20_CLIENT_CPP_WORLD_H
