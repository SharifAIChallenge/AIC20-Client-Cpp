#ifndef AIC20_CLIENT_CPP_TURNMESSAGE_H
#define AIC20_CLIENT_CPP_TURNMESSAGE_H

#include <Model/Cell.h>
#include <Model/World.h>
#include "Core/Message/Message.h"
#include "Core/Message/Parse/ParseError.h"

class TurnMessage final : public Message {
public:
    explicit TurnMessage(json &&root);

    explicit TurnMessage(std::string &&json_form);

    void update_game(Game *_game);
};


#endif //AIC20_CLIENT_CPP_TURNMESSAGE_H
