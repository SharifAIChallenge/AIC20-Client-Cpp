#ifndef AIC20_CLIENT_CPP_GAME_H
#define AIC20_CLIENT_CPP_GAME_H

#include "Core/EventQueue.h"

#include "GameConstants.h"
#include "Map.h"
#include "World.h"
#include "King.h"
#include "Player.h"
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

    void chooseHandById(std::vector<int> typeIds) override;
    void chooseHand(std::vector<const BaseUnit *> baseUnits) override;

    const Player *getMe() override;
    const Player *getFriend() override;
    const Player *getFirstEnemy() override;
    const Player *getSecondEnemy() override;

    const Map *getMap() override;

    std::vector<const Path *> getPathsCrossingCell(const Cell *cell) override;
    std::vector<const Path *> getPathsCrossingCell(int row, int col) override;

    std::vector<const Unit *> getCellUnits(const Cell *cell) override;
    std::vector<const Unit *> getCellUnits(int row, int col) override;

    const Path *getShortestPathToCell(const Player* from_player, const Cell* cell) override;
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
    void castUnitSpell(int unitId, const Path* path, const Cell* cell, const Spell* spell) override;
    void castUnitSpell(int unitId, const Path* path, const Cell* cell, int spellId) override;
    void castUnitSpell(int unitId, const Path* path, int row, int col, const Spell* spell) override;
    void castUnitSpell(int unitId, const Path* path, int row, int col, int spellId) override;
    void castUnitSpell(const Unit *unit, int pathId, const Cell* cell, const Spell* spell) override;
    void castUnitSpell(const Unit *unit, int pathId, const Cell* cell, int spellId) override;
    void castUnitSpell(const Unit *unit, int pathId, int row, int col, const Spell* spell) override;
    void castUnitSpell(const Unit *unit, int pathId, int row, int col, int spellId) override;
    void castUnitSpell(const Unit *unit, const Path* path, const Cell* cell, const Spell* spell) override;
    void castUnitSpell(const Unit *unit, const Path* path, const Cell* cell, int spellId) override;
    void castUnitSpell(const Unit *unit, const Path* path, int row, int col, const Spell* spell) override;
    void castUnitSpell(const Unit *unit, const Path* path, int row, int col, int spellId) override;
    //-----THESE-ARE-NOT-IN-THE-DOC-(BUT-THEY'RE-COOL)-----
    void castUnitSpell(int unitId, int pathId, int index, int spellId) override;
    void castUnitSpell(int unitId, int pathId, int index, const Spell*  spell) override;
    //-----DONE-----

    void castAreaSpell(const Cell* center, const Spell* spell) override;
    void castAreaSpell(const Cell* center, int spellId) override;
    void castAreaSpell(int row, int col, const Spell *spell) override;
    void castAreaSpell(int row, int col, int spellId) override;

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




private:
    EventQueue &event_queue_;

    Map map_;

    GameConstants game_constants_;

    Player players_[4];

    int my_id_;
    int friend_id_;
    int first_enemy_id_;
    int second_enemy_id_;
    int give_friends_id(int id_of_player);
    int give_an_enemy_id(int id_of_player);

    bool got_range_upgrade_;
    bool got_damage_upgrade_;
    int available_range_upgrades_;
    int available_damage_upgrades_;

    int current_turn_;

    int start_time_;

    std::vector<const BaseUnit *> base_units_;

    std::vector<const Spell *> spells_;

    const Spell *received_spell_;
    const Spell *friend_received_spell_;

    bool is_unit_spell_(int typeId);
    bool is_player_or_friend_spell_(int playerId);
    Unit * unit_ptr_by_Id(int unitId);
    const CastSpell* cast_spell_ptr_by_Id(int castSpellId);
    const Path* path_ptr_by_pathId(int pathId);
    const Path* path_from_player_by_pathId(int player_id, int pathId);

    std::vector<const CastSpell *> cast_spell_; //For us

    std::vector<Unit *> ALLunits_; //For us (Used in the TurnMessage parse)

    const Spell *give_spell_by_typeId(int spell_id) const;

    int getTurnTimeout();
    int getPickTimeout();

    int calcShortestPathToCell(const Player* from_player, int row, int col);
    void calcShortestPaths();//Should be called once in init
    std::vector<std::vector<int>> shortestPath2Cell[4]; //For us (4 is for 4 Players)

    friend class InitMessage;

    friend class TurnMessage;

    friend class ShutdownMessage;
};

#endif //AIC20_CLIENT_CPP_GAME_H
