#ifndef AIC20_CLIENT_CPP_EVENT_MESSAGE_H
#define AIC20_CLIENT_CPP_EVENT_MESSAGE_H

#include <string>
#include <vector>

#include "Core/Message/Message.h"


/**
 * A message indicating an event from client
 */
class EventMessage : public Message {
public:

    EventMessage() = default;
    ~EventMessage() override = default;

    EventMessage(const EventMessage&) = default;
    EventMessage& operator=(const EventMessage&) = default;

    EventMessage(EventMessage&&) = default;
    EventMessage& operator=(EventMessage&&) = default;

    /**
     * Construct an event message with the given type and args
     */
    explicit EventMessage(const std::string& type, const std::vector<json>& args);

//    void set_type(const std::string& type);
//    std::string get_type() const;
//
//    void set_args(const std::vector<json>& args);
//    json& get_mutable_args();
//    json get_args() const;

};

#endif // AIC20_CLIENT_CPP_EVENT_MESSAGE_H