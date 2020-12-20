/*  Pokemon Automation Bot Base - Client Example
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_Logging_H
#define PokemonAutomation_Logging_H

#include <sstream>
#include <mutex>
#include "Connection/PABotBaseConnection.h"

namespace PokemonAutomation{

//#define LOG_ALL_MESSAGES


extern std::mutex logging_lock;
void log(const std::stringstream& ss);
void log(const std::string& msg);


std::string current_time();

class MessageLogger : public MessageSnooper{
public:
    virtual void on_send(uint8_t type, const std::string& msg, bool is_retransmit) override;
    virtual void on_recv(uint8_t type, const std::string& msg) override;
};




}
#endif
