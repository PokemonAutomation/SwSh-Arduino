/*  Pokemon Automation Bot Base
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *      This is the main PABotBase class.
 * 
 *  This class represents a connection to a single PABotBase instance running on
 *  a user specified COM port. You can multiple instances of this class if you
 *  are connecting to multiple devices at once.
 * 
 *  This class implements the full communication protocol. So you directly
 *  invoke commands from this class which will be passed on to the Arduino/Teensy.
 * 
 *  All command are synchronous - they will wait until the device returns success
 *  and will automatically handle retransmissions should commands be dropped.
 * 
 * 
 *      Note that button commands will only work if the device is running PABotBase
 *  and is not already running a command. The regular programs do not listen to
 *  button press requests since they are already running their own program.
 * 
 */

#ifndef PokemonAutomation_PABotBase_H
#define PokemonAutomation_PABotBase_H

#include <map>
#include "Common/ControllerDefs.h"
#include "Connection/PABotBaseConnection.h"
#include "Libraries/Logging.h"


class PABotBase : public PABotBaseConnection{
public:
    PABotBase(
        std::unique_ptr<StreamConnection> connection,
        std::chrono::milliseconds retransmit_delay = std::chrono::milliseconds(PABB_RETRANSMIT_DELAY * 1000 / TICKS_PER_SECOND)
    );
    ~PABotBase();

public:
    //  Basic Requests
    uint32_t    protocol_version        ();
    uint32_t    program_version         ();
    uint8_t     program_id              ();
    uint32_t    system_clock            ();
    void        set_leds                (bool on);
    void        end_program_callback    ();


public:
    //  For Command Implementations
    template <
        uint8_t SendType, uint8_t RecvType,
        typename SendParams, typename RecvParams
    >
    void send_request_and_wait(SendParams& send_params, RecvParams& recv_params);
    template <
        uint8_t SendType, uint8_t RecvType,
        typename SendParams, typename RecvParams
    >
    void send_command_and_wait(SendParams& send_params, RecvParams& recv_params);

private:
    template <typename Params> void process_ack(uint8_t type, std::string msg);
    template <typename Params> void process_command_finished(uint8_t type, std::string msg);
    virtual void on_recv_message(uint8_t type, std::string msg) override;

private:
    enum AckState{
        NOT_ACKED,
        ACKED,
        FINISHED,
    };
    struct WaitingAck{
        AckState state = NOT_ACKED;
        uint8_t message_type = 0;
        std::string message_body;
        std::condition_variable cv;
    };

    std::chrono::milliseconds m_retransmit_delay;
    std::mutex m_lock;
    std::map<uint8_t, WaitingAck> m_pending_requests;
};

//  Global instance
extern PABotBase* global_connection;




//  Template Implementations

template <
    uint8_t SendType, uint8_t RecvType,
    typename SendParams, typename RecvParams
>
void PABotBase::send_request_and_wait(SendParams& send_params, RecvParams& recv_params){
    //  Prepare message.
    send_params.seqnum = get_new_seqnum();
    std::string message((const char*)&send_params, sizeof(SendParams));
    std::map<uint8_t, WaitingAck>::iterator iter;
    {
        std::lock_guard<std::mutex> lg(m_lock);
        auto ret = m_pending_requests.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(send_params.seqnum),
            std::forward_as_tuple()
        );
        if (!ret.second){
            throw "Pending sequence number wrap-around.";
        }
        iter = ret.first;
    }

    //  Send message.
    send_message(SendType, message, false);
    auto send_time = std::chrono::system_clock::now();

    //  Wait for ack.
    while (true){
        std::unique_lock<std::mutex> lg(m_lock);
        if (iter->second.state != ACKED){
            iter->second.cv.wait_for(lg, m_retransmit_delay);

            //  Retransmit.
            auto now = std::chrono::system_clock::now();
            if (now - send_time >= m_retransmit_delay){
                send_message(SendType, message, true);
                send_time = now;
            }

            continue;
        }

        //  Verify return payload.
        uint8_t type = iter->second.message_type;
        if (type != RecvType){
            throw "Received incorrect response type: " + std::to_string(type);
        }
        const std::string& body = iter->second.message_body;
        if (body.size() != sizeof(RecvParams)){
            throw "Received incorrect response size: " + std::to_string(body.size());
        }
        memcpy(&recv_params, body.c_str(), body.size());
        m_pending_requests.erase(iter);
        break;
    }

}
template <
    uint8_t SendType, uint8_t RecvType,
    typename SendParams, typename RecvParams
>
void PABotBase::send_command_and_wait(SendParams& send_params, RecvParams& recv_params){
    //  Prepare message.
    send_params.seqnum = get_new_seqnum();
    std::string message((const char*)&send_params, sizeof(SendParams));
    std::map<uint8_t, WaitingAck>::iterator iter;
    {
        std::lock_guard<std::mutex> lg(m_lock);
        auto ret = m_pending_requests.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(send_params.seqnum),
            std::forward_as_tuple()
        );
        if (!ret.second){
            throw "Pending sequence number wrap-around.";
        }
        iter = ret.first;
    }

    //  Send message.
    send_message(SendType, message, false);
    auto send_time = std::chrono::system_clock::now();

    //  Wait for ack.
    while (true){
        std::unique_lock<std::mutex> lg(m_lock);
        if (iter->second.state != NOT_ACKED){
            break;
        }
        iter->second.cv.wait_for(lg, m_retransmit_delay);

        //  Retransmit.
        auto now = std::chrono::system_clock::now();
        if (now - send_time >= m_retransmit_delay){
            send_message(SendType, message, true);
            send_time = now;
        }
    }

    //  Wait for finish.
    while (true){
        std::unique_lock<std::mutex> lg(m_lock);
        if (iter->second.state != FINISHED){
            iter->second.cv.wait(lg);
            continue;
        }

        //  Verify return payload.
        uint8_t type = iter->second.message_type;
        if (type != RecvType){
            throw "Received incorrect response type: " + std::to_string(type);
        }
        const std::string& body = iter->second.message_body;
        if (body.size() != sizeof(RecvParams)){
            throw "Received incorrect response size: " + std::to_string(body.size());
        }
        memcpy(&recv_params, body.c_str(), body.size());
        m_pending_requests.erase(iter);
        break;
    }
}


#endif
