#ifndef AIC20_CLIENT_CPP_MESSAGE_H
#define AIC20_CLIENT_CPP_MESSAGE_H

#include <string>
#include <vector>
#include <memory>

#include <nlohmann/json.hpp>

using nlohmann::json;

/**
 * A json message sent/received across the network
 */
class Message {
public:

    Message() = default;
    virtual ~Message() = default;

    Message(const Message&) = default;
    Message& operator= (const Message&) = default;

    Message(Message&&) = default;
    Message& operator= (Message&&) = default;

    /**
     * Construct a message from a parsed json
     */
    explicit Message(json&& root);

    /**
     * Construct a message from its json form
     */
    explicit Message(std::string&& json_form);

    /**
     * Construct a message with the given name and args
     */
    explicit Message(const std::string& name, const std::vector<json>& args);

    /**
     * @return The message in json string form
     */
    std::string to_string() const;

    void set_name(const std::string& name);
    std::string get_name() const;

    void set_args(const std::vector<json>& args);
    json& get_mutable_args();
    json get_args() const;

    /**
     * Parse and construct the appropriate message from its string form
     *
     * @throws ParseError if the message type is unknown
     * @throws Json::Exception if the message is malformed
     *
     * @return Pointer to the appropriate created message object
     */
    static std::unique_ptr<Message> CreateFromJsonString(const std::string& json_form);

private:

    /// Json tree root
    json m_root;

};

#endif // AIC20_CLIENT_CPP_MESSAGE_H
