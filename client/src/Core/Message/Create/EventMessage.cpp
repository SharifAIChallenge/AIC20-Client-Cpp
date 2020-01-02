#include "EventMessage.h"

EventMessage::EventMessage(const std::string& type, const std::vector<json>& args)
        : Message("event", {})
{
    json one_elem_list = {};
    json json_dic;

    json_dic["type"] = type;
    for (const json& arg : args)
        json_dic["args"] += arg;

    one_elem_list += json_dic;//Just put it in a list []
    Message::get_mutable_args() = one_elem_list;
}

//void EventMessage::set_type(const std::string& type) {
//    Message::get_mutable_args()[0]["type"] = type;
//}

//std::string EventMessage::get_type() const {
//    return Message::get_args()[0]["type"].dump();
//}

//void EventMessage::set_args(const std::vector<json>& args) {
//    Message::get_mutable_args()[0]["args"].clear();
////    Message::get_mutable_args()[0]["args"] = Json::Value(Json::arrayValue);
//    for (const json& arg : args)
//        Message::get_mutable_args()[0]["args"] += arg;
//}

//json& EventMessage::get_mutable_args() {
//    return Message::get_mutable_args()[0]["args"];
//}
//
//json EventMessage::get_args() const {
//    return Message::get_args()[0]["args"];
//}
