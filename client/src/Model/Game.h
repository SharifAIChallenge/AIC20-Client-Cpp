#ifndef AIC20_CLIENT_CPP_GAME_H
#define AIC20_CLIENT_CPP_GAME_H

#include "Core/EventQueue.h"

#include "GameConstants.h"
#include "Map.h"
#include "World.h"
#include "King.h"
#include "Player.h"

class Game final : public World {
public:
    explicit Game(EventQueue &eventQueue);

    ~Game();

    void initData();

    int currentTurn();

    void chooseDeck(std::vector<int> typeIds) override;

    int getMyId() override;

    int getFriendId() override;

    int getFriendId(int player_id) override;

    int getFirstEnemyId() override;

    int getSecondEnemyId() override;

    const Cell *getPlayerPosition(int player_id) override;

    std::vector<const Path *> getPathsFromPlayer(int player_id) override;

    const Path *getPathToFriend(int player_id) override;

    int getMapRowNum() override;

    int getMapColNum() override;

    std::vector<const Path *> getPathsCrossingCell(Cell cell) override;

    std::vector<const Unit *> getPlayerUnits(int player_id) override;

    std::vector<const Unit *> getCellUnits(Cell cell) override;

    const Path *getShortestPathToCell(int from_player, Cell cell) override;

    int getMaxAp() override;

    int getRemainingAp() override;

    std::vector<const BaseUnit *> getHand() override;

    std::vector<const BaseUnit *> getDeck() override;

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

    std::vector<const Unit *> getAreaSpellTargets(const Cell *center, const Spell *spell) override;

    std::vector<const Unit *> getAreaSpellTargets(const Cell *center, int spellId) override;

    std::vector<const Unit *> getAreaSpellTargets(int row, int col, const Spell *spell) override;

    std::vector<const Unit *> getAreaSpellTargets(int row, int col, int spellId) override;

    int getRemainingTurnsToUpgrade() override;

    int getRemainingTurnsToGetSpell() override;

    const CastAreaSpell *getCastAreaSpell(int player_id) override;

    const CastUnitSpell *getCastUnitSpell(int player_id) override;

    std::vector<Spell *> getCastSpellsOnUnit(Unit unit) override;

    std::vector<Spell *> getCastSpellsOnUnit(int unitId) override;

    int getRangeUpgradeNumber() override;

    int getDamageUpgradeNumber() override;

    std::vector<const Spell *> getSpellsList() override;

    std::map<Spell *, int> getSpells() override;

    const Spell *getReceivedSpell() override;

    const Spell *getFriendReceivedSpell() override;

    void upgradeUnitRange(Unit unit) override;

    void upgradeUnitRange(int unitId) override;

    void upgradeUnitDamage(Unit unit) override;

    void upgradeUnitDamage(int unitId) override;

    std::vector<const Unit *> getPlayerDuplicateUnits(int player_id) override;

    std::vector<const Unit *> getPlayerHastedUnits(int player_id) override;

    std::vector<const Unit *> getPlayerPlayedUnits(int player_id) override;

    const Unit *getUnitTarget(Unit unit) override;

    const Unit *getUnitTarget(int unit_id) override;

    const Cell * getUnitTargetCell(Unit unit) override;

    const Cell * getUnitTargetCell(int unit_id) override;

    const Unit *getKingTarget(int player_id) override;

    const Cell * getKingTargetCell(int player_id) override;

    int getKingUnitIsAttackingTo(Unit unit) override;

    int getKingUnitIsAttackingTo(int unit_id) override;

    std::vector<const BaseUnit *> getAllBaseUnits() override;

    std::vector<const Spell *> getAllSpells() override;

    const King *getKingById(int player_id) override;

    const Spell *getSpellById(int spell_id) override;

    const BaseUnit *getBaseUnitById(int type_id) override;

    const std::vector<const Unit *> getPlayerDiedUnits(int player_id) override;

    bool hasPlayerUsedRangeUpgrade(int player_id) override;

    bool hasPlayerUsedDamageUpgrade(int player_id) override;

private:
    EventQueue &event_queue_;

    Map map_;

    GameConstants game_constants_;

    Player players_[4];

    int my_id_;
    int friend_id_;
    int first_enemy_id_;
    int second_enemy_id_;

    bool got_range_upgrade_;
    bool got_damage_upgrade_;
    int available_range_upgrades_;
    int available_damage_upgrades_;

    int current_turn_;

    int start_time_;

    std::vector<const BaseUnit *> base_units_;

    std::vector<const Spell *> spells_;
    std::vector<const Spell *> my_spells_;
    std::vector<const Spell *> friend_spells_;

    const Spell *received_spell_;
    const Spell *friend_received_spell_;

    bool is_unit_spell_(int typeId);
    bool is_player_or_friend_spell_(int playerId);
    const Unit* unit_ptr_by_Id(int unitId);

    std::vector<CastAreaSpell *> cast_area_spell_;
    std::vector<CastUnitSpell *> cast_unit_spell_;

    std::vector<const Path *> paths_from_player_[4];
    const Path *path_to_friend_[4];

    const Spell *spell(int spell_id) const;

    friend class InitMessage;

    friend class TurnMessage;
};

#endif //AIC20_CLIENT_CPP_GAME_H
