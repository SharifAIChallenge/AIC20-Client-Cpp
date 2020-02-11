#ifndef AIC20_CLIENT_CPP_SHUTDOWN_MESSAGE_H
#define AIC20_CLIENT_CPP_SHUTDOWN_MESSAGE_H

#include "Core/Message/Message.h"
#include "Core/Message/Parse/ParseError.h"

class ShutdownMessage : public Message {
public:

    explicit ShutdownMessage(const json &root)
            : Message(root) {
        if (Message::get_type() != "shutdown")
            throw ParseError("Invalid shutdown message");
    }

    explicit ShutdownMessage(const std::string &json_form)
            : Message(json_form) {
        if (Message::get_type() != "shutdown")
            throw ParseError("Invalid shutdown message");
    }

    void update_game(Game *game, json& root);
    void update_result(Game *game, std::map<int, int> &scores);

    void parse_units(json json_units, Game *game, bool is_dead);

    void parse_units_target(Game *game);

};

#endif // AIC20_CLIENT_CPP_SHUTDOWN_MESSAGE_H