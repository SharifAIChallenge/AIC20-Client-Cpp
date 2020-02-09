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

Message::Message(const json &root)
        : m_root(root) {
}

Message::Message(const std::string &json_form) {
    std::istringstream stream(json_form);
    stream >> m_root;
}

Message::Message(const std::string &type,
                 const json &info,
                 const int &turn) {
    set_type(type);
    set_info(info);
    set_turn(turn);
}

std::string Message::to_string() const {
    return m_root.dump();
}

void Message::set_type(const std::string &type) {
    m_root["type"] = type;
}

std::string Message::get_type() const {
    return m_root["type"];
}

void Message::set_info(const json &info) {
    m_root["info"] = info;
}

json &Message::get_mutable_info() {
    return m_root["info"];
}

json Message::get_info() const {
    return m_root["info"];
}

void Message::set_turn(int turn) {
    m_root["turn"] = turn;
}

std::unique_ptr<Message> Message::CreateFromJsonString(const std::string &string_form) {
    json root;


    std::istringstream stream(string_form);
    stream >> root;
//    std::cout << string_form << std::endl;

    //There are three types
    if (root["type"] == "init")
        return std::unique_ptr<InitMessage>(new InitMessage(root));//TODO Fix the IDE error (False Alarm)
    else if (root["type"] == "turn")
        return std::unique_ptr<TurnMessage>(new TurnMessage(root));
    else if (root["type"] == "shutdown")
        return std::unique_ptr<ShutdownMessage>(new ShutdownMessage(root));

    throw ParseError("Unknown message type");
}