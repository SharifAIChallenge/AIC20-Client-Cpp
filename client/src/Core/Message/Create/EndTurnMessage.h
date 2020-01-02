#ifndef AIC20_CLIENT_CPP_END_TURN_MESSAGE_H
#define AIC20_CLIENT_CPP_END_TURN_MESSAGE_H



class EndTurnMessage final : public Message {
public:

    inline explicit EndTurnMessage(int turn)
            : Message("endTurn", {}, turn)
    {}
};

#endif // AIC20_CLIENT_CPP_END_TURN_MESSAGE_H