/*  Pokemon Automation Bot Base
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *      This is the main PABotBase class.
 * 
 *  This class represents a connection to a single PABotBase instance running on
 *  a user specified COM port. You can have multiple instances of this class if
 *  you are connecting to multiple devices at once.
 * 
 *  This class implements the full communication protocol. So you directly
 *  invoke commands from this class which will be passed on to the Arduino/Teensy.
 * 
 *  Requests and commands may be asynchronous. They may return before the device
 *  executes it.
 * 
 * 
 *      Note that button commands will only work if the device is running PABotBase
 *  and is not already running a command. The regular programs do not listen to
 *  button press requests since they are already running their own program.
 * 
 */

#ifndef PokemonAutomation_PABotBase_H
#define PokemonAutomation_PABotBase_H

//#include <iostream>
#include <string.h>
#include <map>
#include <atomic>
#include <condition_variable>
#include <thread>
#include "CommonFramework/ControllerDefs.h"
#include "Connection/PABotBaseConnection.h"
#include "Libraries/Logging.h"


namespace PokemonAutomation{


class PABotBase : public PABotBaseConnection{
    static const size_t MAX_PENDING_REQUESTS = PABB_DEVICE_QUEUE_SIZE;
    static const uint8_t MAX_SEQNUM_GAP = 63;

public:
    PABotBase(
        std::unique_ptr<StreamConnection> connection,
        MessageLogger* logger = nullptr,
        std::chrono::milliseconds retransmit_delay = std::chrono::milliseconds(PABB_RETRANSMIT_DELAY * 1000 / TICKS_PER_SECOND)
    );
    ~PABotBase();

public:
    //  Basic Requests (not thread-safe)
    uint32_t    protocol_version        ();
    uint32_t    program_version         ();
    uint8_t     program_id              ();
    uint32_t    system_clock            ();
    void        set_leds                (bool on);
    void        end_program_callback    ();

    //  Waits for all pending requests to finish.
    void        wait_for_all_requests   ();


public:
    //  For Command Implementations (not thread-safe)

    //  Asynchronous request dispatch.
    template <uint8_t SendType, typename SendParams>
    void issue_request(SendParams& send_params);

    //  Synchronous request.
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
    enum class AckState{
        NOT_ACKED,
        ACKED,
        FINISHED,
    };
    struct PendingRequest{
        AckState state = AckState::NOT_ACKED;
        bool is_command;
        bool silent_remove;
        uint8_t message_type;
        uint8_t ack_type;
        uint8_t finish_type;
        std::string message_body;
        std::string ack_body;
        std::string finish_body;
        std::chrono::system_clock::time_point first_sent;
    };

    uint64_t infer_full_seqnum(uint8_t seqnum) const;
    template <typename Params> void process_ack(uint8_t type, std::string msg);
    template <typename Params> void process_command_finished(uint8_t type, std::string msg);
    virtual void on_recv_message(uint8_t type, std::string msg) override;
    template <uint8_t SendType, typename SendParams>
    std::map<uint64_t, PendingRequest>::iterator issue_request(SendParams& send_params, bool silent_remove);
    void remove_request(std::map<uint64_t, PendingRequest>::iterator iter);

    void sender_thread();

private:
    uint64_t m_send_seq;
    std::chrono::milliseconds m_retransmit_delay;
    std::map<uint64_t, PendingRequest> m_pending_requests;
    std::mutex m_lock;
    std::condition_variable m_cv;
//    bool m_active_wait;
    std::atomic<bool> m_stop;
    std::thread m_sender_thread;
};








//  Global instance
extern PABotBase* global_connection;




//  Template Implementations


template <uint8_t SendType, typename SendParams>
std::map<uint64_t, PABotBase::PendingRequest>::iterator PABotBase::issue_request(SendParams& send_params, bool silent_remove){
    //  Issue a request or a command and return.
    //
    //  If it cannot be issued (because we're over the limits), this function
    //  will wait until it can be issued.
    //
    //  The "silent_remove" parameter determines what to do when the
    //  ack (for a request) or a finish (for a command) is received.
    //
    //  If (silent_remove = true), the receiving thread will remove the request
    //  from the map and do nothing else. This is for async commands.
    //
    //  If (silent_remove = false), the receiving thread will not remove the
    //  request. Instead, it will notify whatever thread is waiting for the
    //  result. That waiting thread will process the return value (if any) and
    //  remove the request from the map. This is for synchronous commands where
    //  the function waits for the command to finish before returning.
    //

//    std::cout << "issue_blocking_request(): " << std::endl;
    uint64_t seqnum = m_send_seq;
    send_params.seqnum = (uint8_t)seqnum;

    std::string message((const char*)&send_params, sizeof(SendParams));
    std::pair<std::map<uint64_t, PendingRequest>::iterator, bool> ret;
    PendingRequest* handle;
    while (true){
        std::unique_lock<std::mutex> lg(m_lock);

        //  Wait until:
        //      1.  The queue is small enough.
        //      2.  The oldest outstanding message isn't too old.
        m_cv.wait(
            lg,
            [&]{
//                std::cout << "issue_request - m_pending_requests.size(): " << m_pending_requests.size() << std::endl;
                return m_pending_requests.size() < MAX_PENDING_REQUESTS &&
                    (m_pending_requests.empty() || seqnum - m_pending_requests.begin()->first < MAX_SEQNUM_GAP);
            }
        );

        ret = m_pending_requests.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(seqnum),
            std::forward_as_tuple()
        );
        if (!ret.second){
            throw "Duplicate sequence number: " + std::to_string(seqnum);
        }
        m_send_seq = seqnum + 1;
        handle = &ret.first->second;
        handle->is_command = PABB_MSG_IS_COMMAND(SendType);
        handle->silent_remove = silent_remove;
        handle->message_type = SendType;
        handle->message_body = std::move(message);
        handle->first_sent = std::chrono::system_clock::now();
        break;
    }

    //  Send message.
    send_message(SendType, handle->message_body, false);
//    handle->last_sent = std::chrono::system_clock::now();

    return ret.first;
}

template <uint8_t SendType, typename SendParams>
void PABotBase::issue_request(SendParams& send_params){
    issue_request<SendType>(send_params, true);
}

template <
    uint8_t SendType, uint8_t RecvType,
    typename SendParams, typename RecvParams
>
void PABotBase::send_request_and_wait(SendParams& send_params, RecvParams& recv_params){
    auto iter = issue_request<SendType>(send_params, false);

    //  Wait for ack.
    std::unique_lock<std::mutex> lg(m_lock);
    m_cv.wait(lg, [&]{ return iter->second.state == AckState::ACKED; });

    //  Verify return payload.
    uint8_t type = iter->second.ack_type;
    if (type != RecvType){
        throw "Received incorrect response type: " + std::to_string(type);
    }
    const std::string& body = iter->second.ack_body;
    if (body.size() != sizeof(RecvParams)){
        throw "Received incorrect response size: " + std::to_string(body.size());
    }
    memcpy(&recv_params, body.c_str(), body.size());
    remove_request(iter);
}
template <
    uint8_t SendType, uint8_t RecvType,
    typename SendParams, typename RecvParams
>
void PABotBase::send_command_and_wait(SendParams& send_params, RecvParams& recv_params){
    auto iter = issue_request<SendType>(send_params, false);

    //  Wait until it's finished.
    std::unique_lock<std::mutex> lg(m_lock);
    m_cv.wait(lg, [&]{ return iter->second.state == AckState::FINISHED; });

    //  Verify return payload.
    uint8_t type = iter->second.ack_type;
    if (type != RecvType){
        throw "Received incorrect response type: " + std::to_string(type);
    }
    const std::string& body = iter->second.ack_body;
    if (body.size() != sizeof(RecvParams)){
        throw "Received incorrect response size: " + std::to_string(body.size());
    }
    memcpy(&recv_params, body.c_str(), body.size());
    remove_request(iter);
    return;
}


}

#endif
