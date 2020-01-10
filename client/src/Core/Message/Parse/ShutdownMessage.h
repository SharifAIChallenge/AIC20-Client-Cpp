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
};

#endif // AIC20_CLIENT_CPP_SHUTDOWN_MESSAGE_H