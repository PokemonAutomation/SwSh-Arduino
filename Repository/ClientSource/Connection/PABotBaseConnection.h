/*  PABotBase Connection
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *      This class wraps a raw SerialConnection object and applies the
 *  communication protocol on top of it. It automatically throws out bad
 *  messsages and passes only the relevant message body onto the child
 *  listener class.
 * 
 *  This class does not handle retransmissions.
 * 
 */

#ifndef PokemonAutomation_PABotBaseConnection_H
#define PokemonAutomation_PABotBaseConnection_H

#include <memory>
#include <string>
#include <deque>
#include <mutex>
#include "ClientSource/Libraries/Compiler.h"
#include "Common/DeviceFramework/MessageProtocol.h"
#include "StreamInterface.h"

namespace PokemonAutomation{

class MessageSniffer{
public:
    virtual void log(std::string msg){}
    virtual void on_send(uint8_t type, const std::string& msg, bool is_retransmit){}
    virtual void on_recv(uint8_t type, const std::string& msg){}
};


class PABotBaseConnection : public StreamListener{
public:
    PABotBaseConnection(std::unique_ptr<StreamConnection> connection);
    ~PABotBaseConnection();

    void set_sniffer(MessageSniffer* sniffer);

public:
    void send_zeros(uint8_t bytes = PABB_MAX_MESSAGE_SIZE);
    void send_message(uint8_t type, const std::string& msg, bool is_retransmit);

protected:
    //  Not thread-safe with sends.
    void safely_stop();

private:
    virtual void on_recv(const void* data, size_t bytes) override;
    virtual void on_recv_message(uint8_t type, std::string msg) = 0;

private:
    std::unique_ptr<StreamConnection> m_connection;
    std::deque<char> m_recv_buffer;

protected:
    MessageSniffer* m_sniffer;
};



}

#endif
