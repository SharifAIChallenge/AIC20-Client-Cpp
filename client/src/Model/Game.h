#ifndef AIC20_CLIENT_CPP_GAME_H
#define AIC20_CLIENT_CPP_GAME_H

#include "Core/EventQueue.h"

#include "GameConstants.h"
#include "Map.h"
#include "World.h"
#include "King.h"
#include "Player.h"
// TODO check input for every func
// TODO optimize the code (remove fors and  etc.)(do all the processat the parsing stage
// TODO write doc for functions

class Game final : public World {
public:
    explicit Game(EventQueue &eventQueue);

    Game(const Game& obj);

    Game operator=(const Game&) = delete;

    ~Game();

    void initPlayerData();

    int currentTurn();

    void chooseDeckById(std::vector<int> typeIds) override;
    void chooseDeck(std::vector<BaseUnit *> baseUnits) override;

    const Player *getMe() override;
    const Player *getFriend() override;
    const Player *getFirstEnemy() override;
    const Player *getSecondEnemy() override;

    const Map *getMap() override;

    std::vector<const Path *> getPathsCrossingCell(Cell cell) override;
    std::vector<const Path *> getPathsCrossingCell(int row, int col) override;

    std::vector<const Unit *> getCellUnits(Cell cell) override;
    std::vector<const Unit *> getCellUnits(int row, int col) override;

    const Path *getShortestPathToCell(const Player* from_player, Cell cell) override;
    const Path *getShortestPathToCell(const Player* from_player, int row, int col) override;

    void putUnit(int typeId, int pathId) override;
    void putUnit(const BaseUnit* baseUnit, int pathId) override;
    void putUnit(int typeId, const Path* path) override;
    void putUnit(const BaseUnit* baseUnit, const Path* path) override;

    int getCurrentTurn() override;

    int getRemainingTime() override;

    void castUnitSpell(int unitId, int pathId, const Cell* cell, const Spell* spell) override;
    void castUnitSpell(int unitId, int pathId, const Cell* cell, int spellId) override;
    void castUnitSpell(int unitId, int pathId, int row, int col, const Spell* spell) override;
    void castUnitSpell(int unitId, int pathId, int row, int col, int spellId) override;
    //-----THESE-ARE-NOT-IN-THE-DOC-(BUT-THE'RE-COOL)-----
    void castUnitSpell(int unitId, int pathId, int index, int spellId) override;
    void castUnitSpell(int unitId, int pathId, int index, Spell spell) override;
    //-----DONE-----

    virtual void castAreaSpell(const Cell* center, const Spell* spell) override;
    virtual void castAreaSpell(const Cell* center, int spellId) override;
    virtual void castAreaSpell(int row, int col, const Spell *spell) override;
    virtual void castAreaSpell(int row, int col, int spellId) override;

    std::vector<const Unit *> getAreaSpellTargets(const Cell *center, const Spell *spell) override;
    std::vector<const Unit *> getAreaSpellTargets(const Cell *center, int spellId) override;
    std::vector<const Unit *> getAreaSpellTargets(int row, int col, const Spell *spell) override;
    std::vector<const Unit *> getAreaSpellTargets(int row, int col, int spellId) override;

    int getRemainingTurnsToUpgrade() override;
    int getRemainingTurnsToGetSpell() override;

    int getRangeUpgradeNumber() override;
    int getDamageUpgradeNumber() override;

    const Spell *getReceivedSpell() override;

    const Spell *getFriendReceivedSpell() override;

    void upgradeUnitRange(const Unit* unit) override;
    void upgradeUnitRange(int unitId) override;
    void upgradeUnitDamage(const Unit* unit) override;
    void upgradeUnitDamage(int unitId) override;

    std::vector<const BaseUnit *> getAllBaseUnits() override;

    std::vector<const Spell *> getAllSpells() override;

    const King *getKingById(int player_id) override;
    const Spell *getSpellById(int spell_id) override;
    const BaseUnit *getBaseUnitById(int type_id) override;
    const Player *getPlayerById(int player_id) override;
    const Unit *getUnitById(int unit_id) override;

    const GameConstants *getGameConstants() override;









//
//    const Cell *getPlayerPosition(int player_id) override;
//
////    std::vector<const Path *> getPathsFromPlayer(int player_id) override;
////
////    const Path *getPathToFriend(int player_id) override;
//
//    int getMapRowNum() override;
//
//    int getMapColNum() override;
//
//    std::vector<const Unit *> getPlayerUnits(int player_id) override;
//
//    int getMaxAp() override;
//
//    int getRemainingAp() override;
//
//    std::vector<const BaseUnit *> getHand() override;
//
//    std::vector<const BaseUnit *> getDeck() override;
//
//    int getMaxTurns() override;
//
//
//    int getPlayerHp(int player_id) override;
//
////    const CastAreaSpell *getCastAreaSpell(int player_id) override;
////
////    const CastUnitSpell *getCastUnitSpell(int player_id) override;
////
////    std::vector<Spell *> getCastSpellsOnUnit(Unit unit) override;
////
////    std::vector<Spell *> getCastSpellsOnUnit(int unitId) override;
//
//
////    std::vector<const Spell *> getSpellsList() override;
//
////    std::map<const Spell *, int> getSpells() override;
//
//    std::vector<const Unit *> getPlayerDuplicateUnits(int player_id) override;
//
//    std::vector<const Unit *> getPlayerHastedUnits(int player_id) override;
//
//    std::vector<const Unit *> getPlayerPlayedUnits(int player_id) override;
//
//    const Unit *getUnitTarget(Unit unit) override;
//
//    const Unit *getUnitTarget(int unit_id) override;
//
//    const Cell * getUnitTargetCell(Unit unit) override;
//
//    const Cell * getUnitTargetCell(int unit_id) override;
//
//    const Unit *getKingTarget(int player_id) override;
//
//    const Cell * getKingTargetCell(int player_id) override;
//
//    int getKingUnitIsAttackingTo(Unit unit) override;
//
//    int getKingUnitIsAttackingTo(int unit_id) override;
//
//    const std::vector<const Unit *> getPlayerDiedUnits(int player_id) override;
//
//    bool hasPlayerUsedRangeUpgrade(int player_id) override;
//
//    bool hasPlayerUsedDamageUpgrade(int player_id) override;

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
    std::map<const Spell *, int> my_spells_map_;
    std::vector<const Spell *> friend_spells_;

    const Spell *received_spell_;
    const Spell *friend_received_spell_;

    bool is_unit_spell_(int typeId);
    bool is_player_or_friend_spell_(int playerId);
    const Unit* unit_ptr_by_Id(int unitId);
    const CastSpell* cast_spell_ptr_by_Id(int castSpellId);
    const Path* path_ptr_by_pathId(int pathId);

//    std::vector<const CastAreaSpell *> cast_area_spell_;
//    std::vector<const CastUnitSpell *> cast_unit_spell_;
    std::vector<const CastSpell *> cast_spell_; //For us

    std::vector<Unit *> ALLunits_; //For us (Used in the TurnMessage parse)

//    std::vector<const Path *> paths_from_player_[4];
//    const Path *path_to_friend_[4];

    const Spell *spell(int spell_id) const;

    int getTurnTimeout();
    int getPickTimeout();

    friend class InitMessage;

    friend class TurnMessage;
};

#endif //AIC20_CLIENT_CPP_GAME_H
