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
        Path* tmp_path_p = new Path();
        tmp_path_p->_pathId = json_path["id"];

        for(json json_cell:json_path["cells"]){
            Cell* tmp_cell_p = new Cell();
            tmp_cell_p->_row = json_cell["row"];
            tmp_cell_p->_column = json_cell["col"];
//            tmp_cell_p->_units

            tmp_path_p->_cells.push_back(tmp_cell_p);
        }
        game->map_.paths_.push_back(tmp_path_p);
    }

//    game->map_.units_

    for(json json_king:json_map["kings"]){
        King* tmp_king_p = new King();
        tmp_king_p->_center._row = json_king["row"];
        tmp_king_p->_center._column = json_king["col"];
//        tmp_king_p->_center._units
        tmp_king_p->_hp = json_king["hp"];
//        tmp_king_p->_level = json_king[]//TODO what is this?
        tmp_king_p->_attack = json_king["attack"];
        tmp_king_p->_range = json_king["range"];
        tmp_king_p->_playerId = json_king["playerId"];

        game->map_.kings_.push_back(tmp_king_p);
    }



}







