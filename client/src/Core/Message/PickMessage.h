#ifndef AIC20_CLIENT_CPP_PICKMESSAGE_H
#define AIC20_CLIENT_CPP_PICKMESSAGE_H


#include <Model/Interface/World.h>
#include "Message.h"
#include "ParseError.h"

class PickMessage final: public Message {
public:
    explicit PickMessage(Json::Value&& root);

    explicit PickMessage(std::string&& json_form);

    void update_game(World* p_world);

};
#endif //AIC20_CLIENT_CPP_PICKMESSAGE_H
