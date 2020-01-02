#include "Message.h"

#include <sstream>
#include <algorithm>
#include <memory>

#include <Utility/Utility.h>
#include <Utility/Logger.h>

#include "Core/Message/Parse/ParseError.h"

#include "Core/Message/Parse/InitMessage.h"
#include "Core/Message/Parse/TurnMessage.h"
#include "Core/Message/Parse/ShutdownMessage.h"
#include "Core/Message/Parse/PickMessage.h"

Message::Message(json&& root)
        : m_root(root)
{
}

Message::Message(std::string&& json_form) {
    std::istringstream stream(json_form);
    stream >> m_root;
}

Message::Message(const std::string& name, const std::vector<json>& args) {
    set_name(name);
    set_args(args);
}

std::string Message::to_string() const {
//    static Json::StreamWriterBuilder builder;
//    builder["indentation"] = "";
//
//    return Json::writeString(builder, m_root);
    return m_root.dump();
}

void Message::set_name(const std::string& name) {
    m_root["name"] = name;
}

std::string Message::get_name() const {
    return m_root["name"].dump();
}

void Message::set_args(const std::vector<json>& args) {
    m_root["args"].clear();
    for (const json& arg : args)
        m_root["args"] += arg;
}

json& Message::get_mutable_args() {
    return m_root["args"];
}

json Message::get_args() const {
    return m_root["args"];
}

std::unique_ptr<Message> Message::CreateFromJsonString(const std::string& string_form) {
    json root;


    std::istringstream stream(string_form);
    stream >> root;

    //There are three types
    if (root["name"] == "init")
        return std::unique_ptr<InitMessage>(new InitMessage(root));//TODO Fix the IDE error (False Alarm)
    else if (root["name"] == "pick")
        return std::unique_ptr<PickMessage>(new PickMessage(root));
    else if (root["name"] == "turn")
        return std::unique_ptr<TurnMessage>(new TurnMessage(root));
    else if (root["name"] == "shutdown")
        return std::unique_ptr<ShutdownMessage>(new ShutdownMessage(root));

    throw ParseError("Unknown message type");
}
