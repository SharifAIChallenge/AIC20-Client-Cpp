#ifndef AIC20_CLIENT_CPP_TURNMESSAGE_H
#define AIC20_CLIENT_CPP_TURNMESSAGE_H

#include "Model/Cell.h"
#include "Model/Game.h"
#include "Model/World.h"
#include "Core/Message/Message.h"
#include "Core/Message/Parse/ParseError.h"

class TurnMessage final : public Message {
public:
    explicit TurnMessage(json &root);

    explicit TurnMessage(const std::string &json_form);

    void update_game(Game *_game);

    void parse_units(json json_units, Game *game, bool is_died);
};


#endif //AIC20_CLIENT_CPP_TURNMESSAGE_H
