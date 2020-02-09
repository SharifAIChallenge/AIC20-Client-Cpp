#ifndef AIC20_CLIENT_CPP_UNIT_H
#define AIC20_CLIENT_CPP_UNIT_H

#include "BaseUnit.h"
#include "Cell.h"
#include "Path.h"
#include "CastSpell.h"
#include "King.h"

class TurnMessage;
class Game;

class Unit {
public:
    Unit() = default;

    ~Unit() = default;

    const BaseUnit *baseUnit() const;

    const Cell *cell() const;

    int unitId() const;

    int playerId() const;

    int hp() const;

    int damageLevel() const;

    int rangeLevel() const;

    int range() const;

    int attack() const;

    bool isDuplicate() const;

    bool isHasted() const;

    const Unit *target() const;

    const Cell *targetCell() const;

    const King *targetIfKing() const;

    const Path *path() const;

    const std::vector<const CastSpell*> affectedSpells() const;

private:
    const BaseUnit *base_unit_;
    Cell *cell_;
    int unit_id_;
    int hp_;
    const Path *path_;
    const Unit *target_;
    const Cell *target_cell_;
    const King *target_if_king_;
    int player_id_;
    int damage_level_;
    int range_level_;
    int range_;
    int attack_;
    bool is_duplicate_;
    bool is_hasted_;
    bool was_played_this_turn_;
    bool was_damage_upgraded_;
    bool was_range_upgraded_;
    std::vector<const CastSpell*> affected_spells_;

    int tmpTargetUnitID = -1;//For Us
    friend class TurnMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_UNIT_H
