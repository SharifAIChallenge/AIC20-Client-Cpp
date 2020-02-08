#include <vector>

#include <Utility/Logger.h>
#include "Utility/Utility.h"
#include "TurnMessage.h"

TurnMessage::TurnMessage(json &root)
        : Message(root) {
    if (Message::get_type() != "turn")
        throw ParseError("Invalid turn message");
}

TurnMessage::TurnMessage(const std::string &json_form)
        : Message(json_form) {
    if (Message::get_type() != "turn")
        throw ParseError("Invalid turn message");
}

void TurnMessage::update_game(Game *game) { //todo big functions!!!
    json root = Message::get_info();

    game->current_turn_ = root["currTurn"];

    game->start_time_ = getTime();

    if(game->base_units_.size() == 0)
        Logger::Get(LogLevel_ERROR) << "BaseUnit list is empty" << std::endl;

    game->players_[game->my_id_].deck_.clear();
    json json_deck = root["deck"];
    for (int typeID : json_deck) {
        game->players_[game->my_id_].deck_.push_back(game->base_units_[typeID]);
    }

    game->players_[game->my_id_].hand_.clear();
    json json_hand = root["hand"];
    for (int typeID : json_hand) {
        game->players_[game->my_id_].hand_.push_back(game->base_units_[typeID]);
    }

    json json_kings = root["kings"];
    for (json json_king : json_kings) {
        int player_id = json_king["playerId"];

        King *king = game->players_[player_id].king_;
        king->hp_ = json_king["hp"];
        king->is_alive_ = json_king["isAlive"];

        int target_id_ = json_king["target"];
        if (target_id_ < 0) {
            king->target_ = game->unit_ptr_by_Id(target_id_);
            king->target_cell_ = king->target_->cell();
        } else {
            king->target_ = nullptr;
            king->target_cell_ = nullptr;
        }


    }



    game->map_.clearUnits();//TODO we might not need this

    //Parsing castSpells
    json castSpells = root["castSpells"];
    for(json json_cSpell: castSpells){
        if(game->is_unit_spell_(json_cSpell["typeId"])){// It's a unit!!!
            CastUnitSpell* cast_unit_spell_ = new CastUnitSpell();
            cast_unit_spell_->caster_id_ = json_cSpell["casterId"];
            cast_unit_spell_->spell_ = game->spell(json_cSpell["typeId"]);
            cast_unit_spell_->id_ = json_cSpell["id"];

            int path_id = json_cSpell["pathId"];
            if(path_id != -1){
                cast_unit_spell_->path_ = game->path_ptr_by_pathId(path_id);
            } else {
                cast_unit_spell_->path_ = nullptr;
            }

            cast_unit_spell_->unit_ = game->unit_ptr_by_Id(json_cSpell["unitId"]);

            int row = json_cSpell["cell"]["row"];
            int col = json_cSpell["cell"]["col"];
            cast_unit_spell_->cell_ = game->map_.cells_[row][col];

            for(json json_aUnit_id:json_cSpell["affectedUnits"]){
                cast_unit_spell_->affected_units_.push_back(
                        game->unit_ptr_by_Id(json_aUnit_id));
            }

            game->players_[cast_unit_spell_->caster_id_].cast_unit_spell = cast_unit_spell_;
//            game->cast_unit_spell_.push_back(cast_unit_spell_);
            game->cast_spell_.push_back(cast_unit_spell_);
        } else {//It's an area spell
            CastAreaSpell* cast_area_spell_ = new CastAreaSpell();
            cast_area_spell_->caster_id_ = json_cSpell["casterId"];
            cast_area_spell_->spell_ = game->spell(json_cSpell["typeId"]);
            cast_area_spell_->id_ = json_cSpell["id"];
            cast_area_spell_->remaining_turns_ = json_cSpell["remainingTurns"];

            int row = json_cSpell["cell"]["row"];
            int col = json_cSpell["cell"]["col"];
            cast_area_spell_->cell_ = game->map_.cells_[row][col];

            for(json json_aUnit_id:json_cSpell["affectedUnits"]){
                cast_area_spell_->affected_units_.push_back(
                        game->unit_ptr_by_Id(json_aUnit_id));
            }

            game->players_[cast_area_spell_->caster_id_].cast_area_spell = cast_area_spell_;
//            game->cast_area_spell_.push_back(cast_area_spell_);
            game->cast_spell_.push_back(cast_area_spell_);
        }

    }

    json json_units = root["units"];
    parse_units(json_units, game, false);
    for (const Unit *unit : game->map_.units_)
        unit->cell_->units_.push_back(unit);

    json json_died_units = root["diedUnits"];
    parse_units(json_died_units, game, true);



    int received_spell = root["receivedSpell"];
    if (received_spell != -1) {
        game->received_spell_ = game->spells_[received_spell];
        game->players_[game->my_id_].spells_.push_back(game->spells_[received_spell]);
    }
    else
        game->received_spell_ = nullptr;

    int friend_received_spell = root["friendReceivedSpell"];
    if (friend_received_spell != -1) {
        game->friend_received_spell_ = game->spells_[friend_received_spell];
        game->players_[game->friend_id_].spells_.push_back(game->spells_[friend_received_spell]);
    }
    else
        game->friend_received_spell_ = nullptr;

    game->my_spells_.clear();
    for (int spell_id : root["mySpells"]) {
        const Spell *spell = game->spell(spell_id);
        game->my_spells_.push_back(spell);
        if (game->my_spells_map_.count(spell))
            game->my_spells_map_[spell] += 1;
        else
            game->my_spells_map_[spell] = 1;
    }

    game->friend_spells_.clear();
    for (int spell_id : root["friendSpells"])
        game->friend_spells_.push_back(game->spell(spell_id));

    game->got_range_upgrade_ = root["gotRangeUpgrade"];
    game->got_damage_upgrade_ = root["gotDamageUpgrade"];
    game->available_range_upgrades_ = root["availableRangeUpgrades"];
    game->available_damage_upgrades_ = root["availableDamageUpgrades"];

    game->players_[game->my_id_].ap_ = root["remainingAP"];
}


void TurnMessage::parse_units(json json_units, Game *game, bool is_died) {

    for (json json_unit : json_units) {
        Unit *unit_p = new Unit();
        unit_p->unit_id_ = json_unit["unitId"];
        unit_p->player_id_ = json_unit["playerId"];

        int type_id = json_unit["typeId"];
        unit_p->base_unit_ = nullptr;
        for (const BaseUnit *base_unit : game->base_units_)
            if (base_unit->typeId() == type_id) {
                unit_p->base_unit_ = base_unit;
                break;
            }
        assert(unit_p->base_unit_ != nullptr);

        int path_id = json_unit["pathId"];
        unit_p->path_ = nullptr;
        for (const Path *path : game->map_.paths_)
            if (path->id() == path_id) {
                unit_p->path_ = path;
                break;
            }

        int row = json_unit["cell"]["row"];
        int col = json_unit["cell"]["col"];
        unit_p->cell_ = game->map_.cells_[row][col];

        unit_p->hp_ = json_unit["hp"];
        unit_p->damage_level_ = json_unit["damageLevel"];
        unit_p->range_level_ = json_unit["rangeLevel"];
        unit_p->is_duplicate_ = json_unit["isDuplicate"];
        unit_p->is_hasted_ = json_unit["isHasted"];

        for(int id_:json_unit["affectedSpells"]) {
            unit_p->affected_spells_.push_back(game->cast_spell_ptr_by_Id(id_));
        }

        unit_p->range_ = json_unit["range"];
        unit_p->attack_ = json_unit["attack"];

        int target_id = json_unit["target"];

        if (target_id < 4) {
            unit_p->target_ = nullptr;
            unit_p->target_if_king_ = game->players_[target_id].king_;
        } else {
            unit_p->target_ = game->unit_ptr_by_Id(target_id);
            unit_p->target_if_king_ = nullptr;
        }

        if (json_unit["targetCell"] != nullptr) {
            int target_row = json_unit["targetCell"]["row"];
            int target_col = json_unit["targetCell"]["col"];
            unit_p->target_cell_ = game->map_.cell(target_row, target_col);
        }

        //Saving the unit
        if(unit_p->was_range_upgraded_) {
            game->players_[unit_p->player_id_].range_upgraded_unit = unit_p;
        }
        if(unit_p->was_damage_upgraded_) {
            game->players_[unit_p->player_id_].damage_upgraded_unit = unit_p;
        }
        if(unit_p->is_duplicate_) {
            game->players_[unit_p->player_id_].duplicate_units_.push_back(unit_p);
        }
        if(unit_p->is_hasted_) {
            game->players_[unit_p->player_id_].hasted_units_.push_back(unit_p);
        }
        if(unit_p->was_played_this_turn_) {
            game->players_[unit_p->player_id_].played_units_.push_back(unit_p);
        }
        if(!is_died) {//Alive
            game->map_.units_.push_back(unit_p);
            game->players_[unit_p->player_id_].units.push_back(unit_p);
        } else {//Dead
            game->map_.died_units_.push_back(unit_p);
            game->players_[unit_p->player_id_].died_units_.push_back(unit_p);
        }

    }
}



