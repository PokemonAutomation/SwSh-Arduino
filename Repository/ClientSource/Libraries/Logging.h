/*  Pokemon Automation Bot Base - Client Example
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_Logging_H
#define PokemonAutomation_Logging_H

#include <sstream>
#include <atomic>
#include <mutex>
#include "ClientSource/Connection/PABotBaseConnection.h"

namespace PokemonAutomation{


extern std::mutex logging_lock;
void log(const std::stringstream& ss);
void log(const std::string& msg);

std::string current_time();


class MessageLogger : public MessageSniffer{
public:
    MessageLogger(bool log_everything = false)
        : m_log_everything(log_everything)
    {}

    std::atomic<bool> m_log_everything;
    virtual void log(std::string msg) override;
    virtual void on_send(uint8_t type, const std::string& msg, bool is_retransmit) override;
    virtual void on_recv(uint8_t type, const std::string& msg) override;
};




}
#endif
