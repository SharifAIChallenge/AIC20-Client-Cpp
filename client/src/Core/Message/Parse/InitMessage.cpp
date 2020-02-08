#include <Utility/Logger.h>
#include "Utility/Utility.h"
#include "InitMessage.h"


InitMessage::InitMessage(const json &root)
        : Message(root) {
    if (Message::get_type() != "init")
        throw ParseError("Invalid init message");
}

InitMessage::InitMessage(const std::string &json_form)
        : Message(json_form) {
    if (Message::get_type() != "init")
        throw ParseError("Invalid init message");
}


void InitMessage::update_game(Game *game) {

    json root = Message::get_info();

    Logger::Get(LogLevel_INFO) << "Starting init Message parse..." << std::endl;

    game->start_time_ = getTime();

    json json_game_const = root["gameConstants"];
    game->game_constants_.max_ap_ = json_game_const["maxAP"];
    game->game_constants_.max_turns_ = json_game_const["maxTurns"];
    game->game_constants_.turn_timeout_ = json_game_const["turnTimeout"];
    game->game_constants_.pick_timeout_ = json_game_const["pickTimeout"];
    game->game_constants_.turns_to_upgrade_ = json_game_const["turnsToUpgrade"];
    game->game_constants_.turns_to_spell_ = json_game_const["turnsToSpell"];
    game->game_constants_.damage_upgrade_addition_ = json_game_const["damageUpgradeAddition"];
    game->game_constants_.range_upgrade_addition_ = json_game_const["rangeUpgradeAddition"];
    game->game_constants_.deck_size_ = json_game_const["deckSize"];
    game->game_constants_.hand_size_ = json_game_const["handSize"];

    json json_map = root["map"];
    game->map_.rows_ = json_map["rows"];
    game->map_.cols_ = json_map["cols"];

    game->map_.initCells();

    for (json json_path:json_map["paths"]) {
        Path *path_p = new Path();
        path_p->id_ = json_path["id"];

        for (json json_cell:json_path["cells"]) {
            int row = json_cell["row"];
            int column = json_cell["col"];

            path_p->cells_.push_back(game->map_.cells_[row][column]);
        }
        game->map_.paths_.push_back(path_p);
    }

//    game->map_.units_
    game->my_id_ = json_map["kings"][0]["playerId"];
    game->friend_id_ = json_map["kings"][1]["playerId"];
    game->first_enemy_id_ = json_map["kings"][2]["playerId"];
    game->second_enemy_id_ = json_map["kings"][3]["playerId"];

    //Initializing the Player
    for (json json_king:json_map["kings"]) {
        King *king_p = new King();

        int row = json_king["center"]["row"];
        int col = json_king["center"]["col"];
        king_p->center_ = game->map_.cells_[row][col];
//        king_p->_center.units_
        king_p->hp_ = json_king["hp"];
        king_p->attack_ = json_king["attack"];
        king_p->range_ = json_king["range"];
        king_p->player_id_ = json_king["playerId"];

        game->players_[king_p->player_id_].king_ = king_p;
        game->map_.kings_.push_back(king_p);
    }

    json json_baseUnits = root["baseUnits"];

    for (json json_baseUnit:json_baseUnits) {
        BaseUnit *baseUnit_p = new BaseUnit();
        baseUnit_p->type_id_ = json_baseUnit["typeId"];
        baseUnit_p->max_hp_ = json_baseUnit["maxHP"];
        baseUnit_p->base_attack_ = json_baseUnit["baseAttack"];
        baseUnit_p->base_range_ = json_baseUnit["baseRange"];

        std::string target = json_baseUnit["target"];
        if (target == "AIR")
            baseUnit_p->target_type_ = AIR;
        else if (target == "GROUND")
            baseUnit_p->target_type_ = GROUND;
        else if (target == "BOTH")
            baseUnit_p->target_type_ = BOTH;
        else
            assert(0);

        baseUnit_p->is_flying_ = json_baseUnit["isFlying"];
        baseUnit_p->is_multiple_ = json_baseUnit["isMultiple"];
        baseUnit_p->ap_ = json_baseUnit["ap"];

        game->base_units_.push_back(baseUnit_p);
    }

    json json_spells = root["spells"];

    for (json json_spell:json_spells) {
        Spell *spell_p = new Spell();
        if(json_spell["type"] == "HP")
            spell_p->type_ = SpellType::HP;
        else if(json_spell["type"] == "TELE")
            spell_p->type_ = SpellType::TELE;
        else if(json_spell["type"] == "DUPLICATE")
            spell_p->type_ = SpellType::DUPLICATE;
        else if(json_spell["type"] == "HASTE")
            spell_p->type_ = SpellType::HASTE;
        else
            throw("InitMessage::Wrong spell_p->type_");
        spell_p->type_id_ = json_spell["typeId"];
        spell_p->duration_ = json_spell["duration"];
        spell_p->priority_ = json_spell["priority"];
        spell_p->range_ = json_spell["range"];
        spell_p->power_ = json_spell["power"];
        spell_p->is_damaging_ = json_spell["isDamaging"];

        std::string target = json_spell["target"];;
        if (target == "SELF")
            spell_p->target_ = SELF;
        else if (target == "ALLIED")
            spell_p->target_ = ALLIED;
        else if (target == "ENEMY")
            spell_p->target_ = ENEMY;
        else
            assert(0);

        game->spells_.push_back(spell_p);
    }

    game->initPlayerData();
}








