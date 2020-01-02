#include "EventMessage.h"

EventMessage::EventMessage(const std::string& type, const std::vector<json>& args)
        : Message("event", {})
{
    set_type(type);
    set_args(args);
}

void EventMessage::set_type(const std::string& type) {
    Message::get_mutable_args()[0]["type"] = type;
}

std::string EventMessage::get_type() const {
    return Message::get_args()[0]["type"].dump();
}

void EventMessage::set_args(const std::vector<json>& args) {
    Message::get_mutable_args()[0]["args"].clear();
//    Message::get_mutable_args()[0]["args"] = Json::Value(Json::arrayValue);
    for (const json& arg : args)
        Message::get_mutable_args()[0]["args"] += arg;
}

json& EventMessage::get_mutable_args() {
    return Message::get_mutable_args()[0]["args"];
}

json EventMessage::get_args() const {
    return Message::get_args()[0]["args"];
}
