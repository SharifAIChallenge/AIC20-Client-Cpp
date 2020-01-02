#ifndef AIC20_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
#define AIC20_CLIENT_CPP_AUTHENTICATION_MESSAGE_H

#include "Core/Message/Message.h"

class AuthenticationMessage : public Message {
public:

    inline explicit AuthenticationMessage(const std::string& token)
            : Message("token", {token})
    {

    }
};

#endif // AIC20_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
