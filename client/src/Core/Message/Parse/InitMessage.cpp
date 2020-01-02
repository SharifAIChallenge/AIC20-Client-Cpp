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

//    json json_map = root["map"];
//    game->map_.

}








