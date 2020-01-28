#ifndef AIC20_CLIENT_CPP_INIT_MESSAGE_H
#define AIC20_CLIENT_CPP_INIT_MESSAGE_H

#include <Model/Map.h>

#include "Core/Message/Message.h"
#include "ParseError.h"
#include <vector>
#include <Model/Game.h>

class InitMessage final : public Message {
public:

    explicit InitMessage(const json &root);

    explicit InitMessage(const std::string &json_form);

    void update_game(Game* game);
};

Map::Map(const Map& map_) {

}

#endif // AIC20_CLIENT_CPP_INIT_MESSAGE_H
