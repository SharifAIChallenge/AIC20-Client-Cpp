#ifndef AIC20_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
#define AIC20_CLIENT_CPP_AUTHENTICATION_MESSAGE_H

#include <vector>

#include "Core/Message/Message.h"

class AuthenticationMessage : public Message {
public:

    inline explicit AuthenticationMessage(const std::string& token)
            : Message("token", {{"token", token},}, 0)
    {

    }
};

#endif // AIC20_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
