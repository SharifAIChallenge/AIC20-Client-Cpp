#ifndef AIC20_CLIENT_CPP_PLAYER_H
#define AIC20_CLIENT_CPP_PLAYER_H

#include <vector>

#include "Spell.h"
#include "BaseUnit.h"
#include "King.h"
#include "Path.h"
#include "CastAreaSpell.h"
#include "CastUnitSpell.h"

class InitMessage;

class TurnMessage;

class Player {
public:
    Player() = default;

    ~Player() = default;

    int playerId() const;

    std::vector<const BaseUnit *> deck() const;

    std::vector<const BaseUnit *> hand() const;

    int ap() const;

    const King *king() const;

    std::vector<const Path *> getPathsFromPlayer() const;

    Path *getPathToFriend() const;

    std::vector<const Unit *> getUnits() const;

    CastAreaSpell *getCastAreaSpell() const;
    CastUnitSpell *getCastUnitSpell() const;

    std::vector<const Unit *> getDuplicateUnits() const;
    std::vector<const Unit *> getHastedUnits() const;
    std::vector<const Unit *> getPlayedUnits() const;
    std::vector<const Unit *> getDiedUnits() const;

    Unit* getRangeUpgradedUnit() const;
    Unit* getDamageUpgradedUnit() const;

    std::vector<const Spell *> spells() const;

    bool isAlive() const;

    int getHp() const;

    int getSpellCount(const Spell* spell);

private:
    int player_id_;
    std::vector<const BaseUnit *> deck_;
    std::vector<const BaseUnit *> hand_;
    int ap_;
    King *king_;
    std::vector<const Path *> paths_from_player_;
    Path* path_to_friend;
    std::vector<const Unit *> units;
    CastAreaSpell* cast_area_spell;
    CastUnitSpell* cast_unit_spell;
    std::vector<const Unit *> duplicate_units_;
    std::vector<const Unit *> hasted_units_;
    std::vector<const Unit *> played_units_;
    std::vector<const Unit *> died_units_;
    Unit* range_upgraded_unit;
    Unit* damage_upgraded_unit;
    std::vector<const Spell *> spells_; //todo remove? (or assign in TurnMessage)

    friend class InitMessage;
    friend class TurnMessage;

    friend class Game;
};


#endif //AIC20_CLIENT_CPP_PLAYER_H
