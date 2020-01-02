#ifndef AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
#define AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H

#include <Core/Message/Message.h>

class CreatePickMessage final: public Message{
public:

    inline explicit CreatePickMessage(int id0,int id1,int id2,int id3,
                                      int id4,int id5,int id6,int id7,
                                      int id8):
            Message("pick",{})
    {
        json tmp_json;
        json id_arr = {id0, id1, id2, id3, id4, id5, id6, id7, id8};
        tmp_json["units"] = id_arr;


        set_args(tmp_json);
    }

};

#endif //AIC20_CLIENT_CPP_CREATEPICKMESSAGE_H
