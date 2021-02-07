/*  Pokemon Automation Bot Base - Client Example
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *      This file contains all messages you can send to PABotBase.
 * 
 */

#ifndef PokemonAutomation_Logging_H
#define PokemonAutomation_Logging_H

#include <stdint.h>
#include <string>
#include <mutex>
#include <iostream>
#include "MessageConverter.h"


//#define LOG_ALL_MESSAGES




class MessageLogger : public MessageSnooper{
public:
    virtual void on_send(uint8_t type, const std::string& msg, bool is_retransmit) override{
        bool print = false;
        do{
            if (is_retransmit){
                print = true;
            }

            //  Request or Command
            if (type >= 0x30){
                print = true;
            }

#ifdef LOG_ALL_MESSAGES
            print = true;
#endif

        }while (false);
        if (!print){
            return;
        }
        std::lock_guard<std::mutex> lg(m_lock);
        if (is_retransmit){
            std::cout << "Re-Send: " << message_to_string(type, msg) << std::endl;
        }else{
            std::cout << "Sending: " << message_to_string(type, msg) << std::endl;
        }
    }
    virtual void on_recv(uint8_t type, const std::string& msg) override{
        bool print = false;
        do{
            //  Info Message
            if ((type & 0xf0) == 0){
                print = true;
            }

#ifdef LOG_ALL_MESSAGES
            print = true;
#endif

        }while (false);
        if (!print){
            return;
        }
        std::lock_guard<std::mutex> lg(m_lock);
        std::cout << "Receive: " << message_to_string(type, msg) << std::endl;
    }

private:
    std::mutex m_lock;
};

#endif
