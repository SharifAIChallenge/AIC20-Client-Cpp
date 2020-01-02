#include "Controller.h"

#include <iostream>
#include <thread>
#include <chrono>

#include <Utility/Utility.h>
#include <Utility/Logger.h>

#include <Network/NetworkError.h>
#include <Core/Message/Parse/PickMessage.h>

#include "Core/Message/Parse/ParseError.h"

#include "Core/Message/Parse/InitMessage.h"
#include "Core/Message/Parse/TurnMessage.h"
#include "Core/Message/Parse/ShutdownMessage.h"
#include "Core/Message/Create/AuthenticationMessage.h"
#include "Core/Message/Create/EndTurnMessage.h"

int Controller::thread_count = 0;

Controller::Controller(const std::string& host, uint16_t port, const std::string& token, unsigned retry_delay)
        : m_token(token)
        , m_retry_delay(retry_delay)
        , m_network(host, port)
        , m_game(m_event_queue)
{
    Logger::Get(LogLevel_DEBUG) << "Server is " << host << ":" << port << std::endl;
    Logger::Get(LogLevel_DEBUG) << "Authentication token is " << token << std::endl;
    Logger::Get(LogLevel_DEBUG) << "Retry delay is " << retry_delay << std::endl;
}

Controller::~Controller() {
    if (m_event_handling_thread.joinable())
        m_event_handling_thread.join();
    if (m_network.is_connected())
        m_network.disconnect();
}

void Controller::run() try {
    Logger::Get(LogLevel_TRACE) << "Enter Controller::run" << std::endl;

    // Connect to the server

    constexpr size_t MAX_RETRY_COUNT = 3;
    for (size_t i = 1; i <= MAX_RETRY_COUNT && !m_network.is_connected(); ++i)
        try {
            Logger::Get(LogLevel_INFO) << "Trying to connect #" << i << std::endl;
            m_network.connect();
        }
        catch (NetworkError &e) {
            if (i == MAX_RETRY_COUNT)
                throw;
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(m_retry_delay));
        }

    Logger::Get(LogLevel_INFO) << "Connected" << std::endl;

    Logger::Get(LogLevel_TRACE) << "Sending authentication message" << std::endl;
    m_network.send(AuthenticationMessage(m_token).to_string());// about the authentication process

    // Now wait for init message
    Logger::Get(LogLevel_TRACE) << "Waiting for init message" << std::endl;

    // Start the event handling thread
    m_event_handling_thread = std::thread(&Controller::event_handling_loop, this);

    while (m_network.is_connected()) {
        Logger::Get(LogLevel_TRACE) << "Waiting for init/pick/turn/shutdown message" << std::endl;

        auto message = Message::CreateFromJsonString(m_network.receive());

        if (InitMessage* init_message = dynamic_cast<InitMessage*>(message.get())) {
            Logger::Get(LogLevel_TRACE) << "Parsing init message" << std::endl;

            m_game.initData();
            init_message->update_game(&m_game);

            Game* _game = new Game(m_game);

            std::thread * preProcThread =
                    new std::thread(Controller::pick_event,&m_client,_game,&(this->m_event_queue));
            m_thread_list.push_back(preProcThread);
        }
        else if (TurnMessage* turn_message = dynamic_cast<TurnMessage*>(message.get())) {
//            Logger::Get(LogLevel_INFO) << "Received Turn message from server" << std::endl;
            Game* _game = new Game(m_game);//copying a from the initial game
            turn_message->update_game(_game);//updating the new game
            Logger::Get(LogLevel_DEBUG) << "Current turn is " << _game->currentTurn() << std::endl;

            Logger::Get(LogLevel_INFO) << "Received Action message from server" << std::endl;

            std::thread* actionThread =
                    new std::thread(Controller::turn_event,&m_client,_game,&(this->m_event_queue));
            m_thread_list.push_back(actionThread);

        }
        else if (dynamic_cast<ShutdownMessage*>(message.get())) {
            Logger::Get(LogLevel_INFO) << "Received shutdown message from server" << std::endl;
            break;
        }



    }
    Logger::Get(LogLevel_INFO) << "Closing the connection" << std::endl;
    m_event_queue.terminate();
    m_network.disconnect();

    Logger::Get(LogLevel_INFO) << "Joining all threads" << std::endl;
    for (std::thread * _thread : m_thread_list){
        _thread->join();
        delete _thread;
    }

    Logger::Get(LogLevel_TRACE) << "Exit Controller::run" << std::endl;


}
catch (json::exception&) {
    throw ParseError("Malformed json string");
}

void Controller::event_handling_loop() noexcept {
    while (m_network.is_connected()) {
        auto message = m_event_queue.pop();
        if (!message)
            break;
        m_network.send(message->to_string());
    }
}

void Controller::pick_event(AI* client,Game* tmp_game, EventQueue *m_event_queue) {
    int THREAD_NUM = Controller::thread_count++;
    try {
        Logger::Get(LogLevel_DEBUG) << "Launched pick Thread #" << THREAD_NUM << std::endl;
        client->pick(tmp_game);
    }catch(const char* err_msg){
        Logger::Get(LogLevel_ERROR) << "Error in pick Thread #" << THREAD_NUM << std::endl <<
                                    err_msg << std::endl;
    }

    Logger::Get(LogLevel_TRACE) << "pick:Sending end message with turn = " << tmp_game->currentTurn() << std::endl;
    m_event_queue->push(EndTurnMessage("pick-end",{tmp_game->currentTurn()}));

    delete tmp_game;
    Logger::Get(LogLevel_DEBUG) << "End of pick Thread #" << THREAD_NUM << std::endl;
}

void Controller::turn_event(AI* client,Game* tmp_game, EventQueue *m_event_queue) {
    int THREAD_NUM = Controller::thread_count++;
    try {
        Logger::Get(LogLevel_DEBUG) << "Launched action Thread #" << THREAD_NUM << std::endl;
        client->turn(tmp_game);
    }catch(const char* err_msg){
        Logger::Get(LogLevel_ERROR) << "Error in action Thread #" << THREAD_NUM << std::endl<<
                                    err_msg << std::endl;
    }

    Logger::Get(LogLevel_TRACE) << "action:Sending end message with turn = " << tmp_game->currentTurn() << std::endl;
    m_event_queue->push(EndTurnMessage("action-end",{tmp_game->currentTurn()}));

    delete tmp_game;
    Logger::Get(LogLevel_DEBUG) << "End of action Thread #" << THREAD_NUM << std::endl;
}

