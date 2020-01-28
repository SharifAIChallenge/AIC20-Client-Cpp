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

    const King *getKingById(int player_id) override;

    const Map *getMap() const override;

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

    CastAreaSpell *cast_area_spell_[4];
    CastUnitSpell *cast_unit_spell_[4];

    std::vector<BaseUnit *> base_units_;

    std::vector<const Spell *> spells_; // todo spell id does not start with 0
    std::vector<const Spell *> my_spells_;
    std::vector<const Spell *> friend_spells_;

    const Spell *received_spell_;
    const Spell *friend_received_spell_;

    std::vector<int> deck_;//TODO baseUnit
    std::vector<int> hand_;//TODO baseUnit

    std::vector<const Path *> paths_from_player_[4];
    const Path *path_to_friend_[4];

    const Spell *spell(int spell_id) const;

    friend class InitMessage;

    friend class TurnMessage;
};

#endif //AIC20_CLIENT_CPP_GAME_H
