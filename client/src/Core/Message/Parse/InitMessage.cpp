#include <Utility/Logger.h>
#include "InitMessage.h"


InitMessage::InitMessage(json root)
        : Message(root)
{
    if (Message::get_name() != "init")
        throw ParseError("Invalid init message");
}

InitMessage::InitMessage(std::string&& json_form)
        : Message(json_form)
{
    if (Message::get_name() != "init")
        throw ParseError("Invalid init message");
}


void InitMessage::update_game(Game *game) {

    json root = Message::get_args()[0];

    Logger::Get(LogLevel_INFO) << "Starting init Message parse..." << std::endl;

    json json_game_const = root["gameConstants"];
    game->game_constants_.max_ap_ = json_game_const["maxAP"];
    game->game_constants_.max_turns_ = json_game_const["maxTurns"];
    game->game_constants_.turn_timeout_ = json_game_const["turnTimeout"];
    game->game_constants_.pick_timeout_ = json_game_const["pickTimeout"];
    game->game_constants_.turns_to_upgrade_ = json_game_const["turnsToUpgrade"];
    game->game_constants_.turns_to_spell_ = json_game_const["turnsToSpell"];
    game->game_constants_.damage_upgrade_addition_ = json_game_const["damageUpgradeAddition"];
    game->game_constants_.range_upgrade_addition_ = json_game_const["rangeUpgradeAddition"];

    json json_map = root["map"];
    game->map_.rows_ = json_map["rows"];
    game->map_.cols_ = json_map["cols"];

    for(json json_path:json_map["paths"]){
        Path* path_p = new Path();
        path_p->path_id_ = json_path["id"];

        for(json json_cell:json_path["cells"]){
            Cell* cell_p = new Cell();
            cell_p->_row = json_cell["row"];
            cell_p->_column = json_cell["col"];
//            cell_p->_units

            path_p->cells_.push_back(cell_p);
        }
        game->map_.paths_.push_back(path_p);
    }

//    game->map_.units_

    for(json json_king:json_map["kings"]){
        King* king_p = new King();
        king_p->center_._row = json_king["row"];
        king_p->center_._column = json_king["col"];
//        king_p->_center._units
        king_p->hp_ = json_king["hp"];
//        king_p->_level = json_king[]//TODO what is this?
        king_p->attack_ = json_king["attack"];
        king_p->range_ = json_king["range"];
        king_p->playerId_ = json_king["playerId"];

        game->map_.kings_.push_back(king_p);
    }

    json json_baseUnits = root["baseUnits"];

    for(json json_baseUnit:json_baseUnits){
        BaseUnit * baseUnit_p = new BaseUnit();
        baseUnit_p->type_ = json_baseUnit["typeId"];//TODO type(?)
        baseUnit_p->maxHP_ = json_baseUnit["maxHP"];
        baseUnit_p->attack_ = json_baseUnit["baseAttack"];
        baseUnit_p->range_ = json_baseUnit["baseRange"];
        baseUnit_p->target_ = json_baseUnit["target"];//TODO type(?)
        baseUnit_p->isFlying_ = json_baseUnit["isFlying"];
        baseUnit_p->isMultiple_ = json_baseUnit["isMultiple"];
        baseUnit_p->ap_ = json_baseUnit["ap"];

        game->base_units.push_back(baseUnit_p);
    }

    json json_spells = root["spells"];

    for(json json_spell:json_spells){
        Spell * spell_p = new Spell();
        spell_p->turnEffect_ = json_spell["type"];
        spell_p->type_ = json_spell["typeId"];
        spell_p->duration_ = json_spell["duration"];
        spell_p->priority_ = json_spell["priority"];
        spell_p->range_ = json_spell["range"];
        spell_p->power_ = json_spell["power"];
        spell_p->target_ = json_spell["target"];

        game->spells.push_back(spell_p);
    }

}








