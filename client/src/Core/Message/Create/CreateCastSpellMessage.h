#ifndef AIC20_CLIENT_CPP_CREATECASTSPELLMESSAGE_H
#define AIC20_CLIENT_CPP_CREATECASTSPELLMESSAGE_H

#include <Core/Message/Message.h>

class CreateCastSpellMessage final : public Message {
public:

    inline explicit CreateCastSpellMessage(int turn, int typeID, int cell_row,
                                           int cell_col, int unitID, int pathID) :
            Message("castSpell", {}, turn) {
        json tmp_json, tmp_cell;
        tmp_json["typeId"] = typeID;
        tmp_cell["row"] = cell_row;
        tmp_cell["col"] = cell_col;
        tmp_json["cell"] = tmp_cell;
        tmp_json["unitId"] = unitID;
        tmp_json["pathId"] = pathID;

        set_info(tmp_json);
    }

};

#endif //AIC20_CLIENT_CPP_CREATECASTSPELLMESSAGE_H
