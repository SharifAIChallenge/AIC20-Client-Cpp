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

    const BaseUnit *getBaseUnit() const;

    const Cell *getCell() const;

    int getUnitId() const;

    int getPlayerId() const;

    int getHp() const;

    int getDamageLevel() const;

    int getRangeLevel() const;

    int getRange() const;

    int getAttack() const;

    bool isDuplicate() const;

    bool isHasted() const;

    const Unit *getTarget() const;

    const Cell *getTargetCell() const;

    const King *getTargetIfKing() const;

    const Path *getPath() const;

    const std::vector<const CastSpell*> getAffectedSpells() const;

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
    friend class ShutdownMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_UNIT_H
