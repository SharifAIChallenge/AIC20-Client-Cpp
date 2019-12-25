#ifndef AIC20_CLIENT_CPP_GAME_H
#define AIC20_CLIENT_CPP_GAME_H

#include <Core/EventQueue.h>

#include "World.h"
#include "Map.h"

class Game : public World {
public:
    explicit Game(EventQueue &eventQueue);

    int currentTurn();

    void initData();

    void chooseDeck(std::vector<int *> typeIds) override;

    int getMyId() override;

    int getFriendId() override;

    Cell getPLayerPosition(int playerId) override;

    std::vector<Path *> getPathsFromPlayer(int playerID) override;

    Path getPathToFriend(int playerId) override;

    int getMapHeight() override;

    int getMapWidth() override;

    std::vector<Path *> getPathsCrossingCell(Cell cell) override;

    std::vector<Unit *> getPlayerUnits(int playerId) override;

    std::vector<Unit *> getCellUnits(Cell cell) override;

    Path getShortestPathToCell(int fromPlayerId, Cell cell) override;

    int getMaxAp() override;

    int getRemainingAp() override;

    std::vector<Unit *> getHand() override;

    std::vector<Unit *> getDeck() override;

    void playUnit(int typeId, int pathId) override;

    int getCurrentTurn() override;

    int getMaxTurns() override;

    int getPickTimeout() override;

    int getTurnTimeout() override;

    int getRemainingTime() override;

    int getPlayerHp(int playerId) override;

    void castUnitSpell(int unitId, int pathId, int index, int spellId) override;

    void castUnitSpell(int unitId, int pathId, int index, Spell spell) override;

    void castAreaSpell(Cell center, int spellId) override;

    void castAreaSpell(Cell center, Spell spell) override;

    std::vector<Unit *> getAreaSpellTargets(Cell center, Spell spell) override;

    std::vector<Unit *> getAreaSpellTargets(Cell center, int SpellId) override;

    int getRemainingTurnsToUpgrade() override;

    int getRemainingTurnsToGetSpell() override;

    CastAreaSpell getCastAreaSpell(int playerId) override;

    CastUnitSpell getCastUnitSpell(int playerId) override;

    std::vector<CastAreaSpell *> getActiveSpellsOnCell(Cell cell) override;

    int getUpgradeTokenNumber() override;

    std::vector<Spell *> getSpells() override;

    Spell getRecievedSpell() override;

    Spell getFriendRecievedSpell() override;

private:
    EventQueue &_event_queue;

    Map _map;

    int _current_turn;
};

#endif //AIC20_CLIENT_CPP_GAME_H
