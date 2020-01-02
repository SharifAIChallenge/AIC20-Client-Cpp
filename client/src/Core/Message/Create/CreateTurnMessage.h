#ifndef AIC20_CLIENT_CPP_CREATECASTMESSAGE_H
#define AIC20_CLIENT_CPP_CREATECASTMESSAGE_H


#include "Core/Message/Create/EventMessage.h"


class CreateTurnMessage final: public EventMessage{
public:
    inline explicit CreateTurnMessage():
            EventMessage("cast",{})
    {
    }

};

#endif //AIC20_CLIENT_CPP_CREATECASTMESSAGE_H
