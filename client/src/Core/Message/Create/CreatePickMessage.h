#ifndef AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
#define AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H

#include <vector>

#include <Core/Message/Message.h>

class CreatePickMessage final: public Message{
public:

    inline explicit CreatePickMessage(const std::vector<int> &ids):
            Message("pick",{},0)
    {
        json tmp_json;
        json id_arr(ids);
        tmp_json["units"] = id_arr;

        set_info(tmp_json);
    }

};

#endif //AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
