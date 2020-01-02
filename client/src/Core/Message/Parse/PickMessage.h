#ifndef AIC20_CLIENT_CPP_PICKMESSAGE_H
#define AIC20_CLIENT_CPP_PICKMESSAGE_H


#include <Model/World.h>
#include "Core/Message/Message.h"
#include "Core/Message/Parse/ParseError.h"

class PickMessage final: public Message {
public:
    explicit PickMessage(json&& root);

    explicit PickMessage(std::string&& json_form);

    void update_game(World* p_world);

};
#endif //AIC20_CLIENT_CPP_PICKMESSAGE_H
