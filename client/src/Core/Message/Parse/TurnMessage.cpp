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

    json json_deck = root["deck"];
    for(int typeID : json_deck){
        game->deck.push_back(typeID);
    }

    json json_hand = root["hand"];
    for(int typeID : json_hand){
        game->hand.push_back(typeID);
    }

    json json_kings = root["kings"];


}





