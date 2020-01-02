#ifndef AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
#define AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H

#include <Core/Message/Message.h>

class CreateRangeUpgradeMessage final: public Message{
public:

    inline explicit CreateRangeUpgradeMessage(int turn,int unitID):
            Message("rangeUpgrade", {}, turn)
    {
        json tmp_json;
        tmp_json["unitId"] = unitID;

        set_info(tmp_json);
    }

};

#endif //AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
