#ifndef AIC20_CLIENT_CPP_UNIT_H
#define AIC20_CLIENT_CPP_UNIT_H

#include "BaseUnit.h"
#include "Cell.h"
#include "Path.h"
#include "CastSpell.h"

class TurnMessage;
class Game;

class Unit {
public:
    Unit() = default;

    ~Unit() = default;

    const Cell *cell() const;

    int unitId() const;

    int playerId() const;

    int hp() const;

    int damageLevel() const;

    int rangeLevel() const;

    int range() const;

    int attack() const;

    bool wasPlayedThisTurn() const;

    bool wasDamageUpgraded() const;

    bool wasRangeUpgraded() const;

    bool isDuplicate() const;

    bool isHasted() const;

    const Cell *targetCell() const;

    const BaseUnit *baseUnit() const;

    const Path *path() const;

    const std::vector<const CastSpell*> affectedSpells() const;

private:
    int player_id_;
    int unit_id_;
    int hp_;
    int damage_level_;
    int range_level_;
    int range_;
    int attack_;
    bool was_played_this_turn_;
    bool was_damage_upgraded_;
    bool was_range_upgraded_;
    bool is_duplicate_;
    bool is_hasted_;

    int target_id_;
    const Cell *target_cell_;

    Cell *cell_;
    const BaseUnit *base_unit_;
    const Path *path_;

    std::vector<const CastSpell*> affected_spells;

    friend class TurnMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_UNIT_H
