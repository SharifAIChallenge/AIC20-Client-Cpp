#ifndef AIC20_CLIENT_CPP_CREATECASTMESSAGE_H
#define AIC20_CLIENT_CPP_CREATECASTMESSAGE_H


#include <Core/Message/Message.h>


class CreateDamageUpgradeMessage final: public Message{
public:
    inline explicit CreateDamageUpgradeMessage(
            std::string type, ):
            EventMessage("cast")
    {

    }

};

#endif //AIC20_CLIENT_CPP_CREATECASTMESSAGE_H
