#ifndef AIC20_CLIENT_CPP_CREATECASTMESSAGE_H
#define AIC20_CLIENT_CPP_CREATECASTMESSAGE_H


#include <Core/Message/Message.h>


class CreateDamageUpgradeMessage final: public Message{
public:
    inline explicit CreateDamageUpgradeMessage(
            int turn, int unitID):
            Message("rangeUpgrade", {}, turn)
    {
        json tmp_json;
        tmp_json["unitId"] = unitID;

        set_info(tmp_json);
    }

};

#endif //AIC20_CLIENT_CPP_CREATECASTMESSAGE_H
