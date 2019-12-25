#ifndef AIC20_CLIENT_CPP_TURNMESSAGE_H
#define AIC20_CLIENT_CPP_TURNMESSAGE_H

#include <Model/Cell.h>
#include <Model/World.h>
#include "Message.h"
#include "ParseError.h"

class TurnMessage final : public Message {
public:
    explicit TurnMessage(Json::Value &&root);

    explicit TurnMessage(std::string &&json_form);

    void update_game(World *_game);
};


#endif //AIC20_CLIENT_CPP_TURNMESSAGE_H
