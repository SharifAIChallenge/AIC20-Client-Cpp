#include <Utility/Logger.h>
#include "TurnMessage.h"

TurnMessage::TurnMessage(json&& root)
        : Message(root)
{
    if (Message::get_type() != "turn")//TODO are we sure this is being sent in the JSON string?
        throw ParseError("Invalid turn message");
}

TurnMessage::TurnMessage(std::string&& json_form)
        : Message(json_form)
{
    if (Message::get_type() != "turn")
        throw ParseError("Invalid turn message");
}

void TurnMessage::update_game(Game *game) {
    json root = Message::get_info()[0];

    game->current_turn_ = root["currTurn"];

    json json_deck = root["deck_"];
    for(int typeID : json_deck){
        game->deck_.push_back(typeID);
    }

    json json_hand = root["hand_"];
    for(int typeID : json_hand){
        game->hand_.push_back(typeID);
    }

    json json_kings = root["kings"];
    for(json king : json_kings){//TODO maybe update game->players_[4] as well
        // Find the King in the map and update it
        int tmpID = king["playerId"];
        for(King* king_p : game->map_.kings_){
            if(tmpID == king_p->playerID()){
                // Here we apply the changes
                king_p->hp_ = king["hp"];
                king_p->isAlive_ = king["isAlive"];
            }
        }
    }

    json json_units = root["units"];
    for(json json_unit : json_units){
        Unit* unit_p = new Unit();
        unit_p->_unitId = json_unit["unitId"];
        unit_p->_playerId = json_unit["playerId"];
        unit_p->_unitId = json_unit["typeId"];//
        unit_p->_unitId = json_unit["pathId"];//
        unit_p->_unitId = json_unit["cell"]["row"];//TODO so are we going to use a pointer?
        unit_p->_unitId = json_unit["cell"]["col"];//
        unit_p->_hp = json_unit["hp"];
        unit_p->_unitId = json_unit["damageLevel"];//TODO aren't these in the BaseUnit?!?!
        unit_p->_unitId = json_unit["rangeLevel"];//TODO aren't these in the BaseUnit?!?!
        unit_p->_unitId = json_unit["wasDamageUpgraded"];//
        unit_p->_unitId = json_unit["wasRangeUpgraded"];//
        unit_p->_isHasted = json_unit["isHasted"];
        unit_p->_unitId = json_unit["isClone"];//
        unit_p->_unitId = json_unit["activePoisons"];//TODO What?
        unit_p->_unitId = json_unit["range"];//TODO aren't these in the BaseUnit?!?!
        unit_p->_unitId = json_unit["attack"];//TODO aren't these in the BaseUnit?!?!
        unit_p->_unitId = json_unit["wasPlayedThisTurn"];//
        unit_p->_unitId = json_unit["target"];//TODO aren't these in the BaseUnit?!?!
    }

}





