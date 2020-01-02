#ifndef AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
#define AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H

#include <Core/Message/Message.h>

class CreatePutUnitMessage final: public Message{
public:

    inline explicit CreatePutUnitMessage(int turn, int typeID, int pathID):
            Message("putUnit",{},turn)
    {
        json tmp_json;
        tmp_json["typeId"] = typeID;
        tmp_json["pathId"] = pathID;

        set_info(tmp_json);
    }

};

#endif //AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
