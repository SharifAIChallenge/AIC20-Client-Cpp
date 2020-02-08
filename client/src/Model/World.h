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

//todo change all vector getters to const ref
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

    virtual const Cell *getPlayerPosition(int player_id) = 0;

    virtual std::vector<const Path *> getPathsFromPlayer(int player_id) = 0;

    virtual const Path *getPathToFriend(int player_id) = 0;

    virtual int getMapRowNum() = 0;

    virtual int getMapColNum() = 0;

    virtual std::vector<const Path *> getPathsCrossingCell(Cell cell) = 0;

    virtual std::vector<const Unit *> getPlayerUnits(int player_id) = 0;

    virtual std::vector<const Unit *> getCellUnits(Cell cell) = 0;

    virtual const Path *getShortestPathToCell(int from_player, Cell cell) = 0;

    virtual int getMaxAp() = 0;

    virtual int getRemainingAp() = 0;

    virtual std::vector<const BaseUnit *> getHand() = 0;

    virtual std::vector<const BaseUnit *> getDeck() = 0;

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

    virtual std::vector<const Unit *> getAreaSpellTargets(const Cell *center, const Spell *spell) = 0;

    virtual std::vector<const Unit *> getAreaSpellTargets(const Cell *center, int spellId) = 0;

    virtual std::vector<const Unit *> getAreaSpellTargets(int row, int col, const Spell *spell) = 0;

    virtual std::vector<const Unit *> getAreaSpellTargets(int row, int col, int spellId) = 0;

    virtual int getRemainingTurnsToUpgrade() = 0;

    virtual int getRemainingTurnsToGetSpell() = 0;

    virtual const CastAreaSpell * getCastAreaSpell(int player_id) = 0;

    virtual const CastUnitSpell * getCastUnitSpell(int player_id) = 0;

    virtual std::vector<Spell *> getCastSpellsOnUnit(Unit unit) = 0;

    virtual std::vector<Spell *> getCastSpellsOnUnit(int unitId) = 0;

    virtual int getRangeUpgradeNumber() = 0;

    virtual int getDamageUpgradeNumber() = 0;

    virtual std::vector<const Spell *> getSpellsList() = 0;

    virtual std::map<const Spell *, int> getSpells() = 0; //todo remove??


    virtual const Spell *getReceivedSpell() = 0;

    virtual const Spell *getFriendReceivedSpell() = 0;


    virtual void upgradeUnitRange(Unit unit) = 0;

    virtual void upgradeUnitRange(int unitId) = 0;

    virtual void upgradeUnitDamage(Unit unit) = 0;

    virtual void upgradeUnitDamage(int unitId) = 0;


    virtual std::vector<const Unit *> getPlayerDuplicateUnits(int player_id) = 0;

    virtual std::vector<const Unit *> getPlayerHastedUnits(int player_id) = 0;

    virtual std::vector<const Unit *> getPlayerPlayedUnits(int player_id) = 0;


    virtual const Unit *getUnitTarget(Unit unit) = 0;

    virtual const Unit *getUnitTarget(int unit_id) = 0;

    virtual const Cell * getUnitTargetCell(Unit unit) = 0;

    virtual const Cell * getUnitTargetCell(int unit_id) = 0;

    virtual const Unit *getKingTarget(int player_id) = 0;

    virtual const Cell * getKingTargetCell(int player_id) = 0;

    virtual int getKingUnitIsAttackingTo(Unit unit) = 0;

    virtual int getKingUnitIsAttackingTo(int unit_id) = 0;


    virtual std::vector<const BaseUnit *> getAllBaseUnits() = 0;

    virtual std::vector<const Spell *> getAllSpells() = 0;


    virtual const King *getKingById(int player_id) = 0;

    virtual const Spell *getSpellById(int spell_id) = 0;

    virtual const BaseUnit *getBaseUnitById(int type_id) = 0;

    virtual const std::vector<const Unit *> getPlayerDiedUnits(int player_id) = 0;

    virtual bool hasPlayerUsedRangeUpgrade(int player_id) = 0;

    virtual bool hasPlayerUsedDamageUpgrade(int player_id) = 0;
};


#endif //AIC20_CLIENT_CPP_WORLD_H
