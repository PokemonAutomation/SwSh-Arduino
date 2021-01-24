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

#include <string.h>
#include <map>
#include <atomic>
#include <condition_variable>
#include <thread>
#include "ClientSource/CommonFramework/ControllerDefs.h"
#include "ClientSource/Connection/PABotBaseConnection.h"
#include "ClientSource/Libraries/Logging.h"

#include <iostream>
using std::cout;
using std::endl;


namespace PokemonAutomation{

struct CancelledException{};


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

    void connect();
    void stop();

    enum class State{
        RUNNING,
        STOPPING,
        STOPPED,
    };
    State state() const{ return m_state.load(std::memory_order_acquire); }

public:
    //  Basic Requests
    uint32_t    protocol_version        ();
    uint32_t    program_version         ();
    uint8_t     program_id              ();
    uint32_t    system_clock            ();
    void        set_leds                (bool on);
    void        end_program_callback    ();

    //  Waits for all pending requests to finish.
    void        wait_for_all_requests   ();


public:
    //  For Command Implementations

    //  Asynchronous request dispatch.
    template <uint8_t SendType, typename SendParams>
    bool try_issue_request(SendParams& send_params);
    template <uint8_t SendType, typename SendParams>
    void issue_request(SendParams& send_params);

    //  Synchronous request.
    template <
        uint8_t SendType, uint8_t RecvType,
        typename SendParams, typename RecvParams
    >
    void issue_and_wait(SendParams& send_params, RecvParams& recv_params);


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
    bool issue_request(
        std::map<uint64_t, PendingRequest>::iterator& iter,
        SendParams& send_params,
        bool blocking, bool silent_remove
    );
    void remove_request(std::map<uint64_t, PendingRequest>::iterator iter);

    void sender_thread();


private:
    uint64_t m_send_seq;
    std::chrono::milliseconds m_retransmit_delay;
    std::map<uint64_t, PendingRequest> m_pending_requests;
    std::mutex m_lock;
    std::condition_variable m_cv;
    std::atomic<State> m_state;
    std::thread m_sender_thread;
};








//  Global instance
extern PABotBase* global_connection;




//  Template Implementations


template <uint8_t SendType, typename SendParams>
bool PABotBase::issue_request(
    std::map<uint64_t, PendingRequest>::iterator& iter,
    SendParams& send_params,
    bool blocking, bool silent_remove
){
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

    std::unique_lock<std::mutex> lg(m_lock);

    uint64_t seqnum;
    while (true){
        if (m_state.load(std::memory_order_acquire) != State::RUNNING){
            throw CancelledException();
        }

        seqnum = m_send_seq;

        //  Command queue is not full.
        bool queue_ok = !PABB_MSG_IS_COMMAND(SendType) || m_pending_requests.size() < MAX_PENDING_REQUESTS;

        //  Oldest outstanding message isn't too old.
        bool seq_ok = m_pending_requests.empty() || seqnum - m_pending_requests.begin()->first < MAX_SEQNUM_GAP;

        if (queue_ok && seq_ok){
            break;
        }

        if (!blocking){
            return false;
        }

        m_cv.wait(lg);
    }

    send_params.seqnum = (uint8_t)seqnum;

    std::pair<std::map<uint64_t, PendingRequest>::iterator, bool> ret = m_pending_requests.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(seqnum),
        std::forward_as_tuple()
    );
    if (!ret.second){
        throw "Duplicate sequence number: " + std::to_string(seqnum);
    }
    m_send_seq = seqnum + 1;
    PendingRequest* handle = &ret.first->second;
    handle->is_command = PABB_MSG_IS_COMMAND(SendType);
    handle->silent_remove = silent_remove;
    handle->message_type = SendType;
    handle->message_body = std::string((const char*)&send_params, sizeof(SendParams));
    handle->first_sent = std::chrono::system_clock::now();


    //  Send message.
    send_message(SendType, handle->message_body, false);
//    handle->last_sent = std::chrono::system_clock::now();

    iter = ret.first;
    return true;
}

template <uint8_t SendType, typename SendParams>
bool PABotBase::try_issue_request(SendParams& send_params){
    std::map<uint64_t, PendingRequest>::iterator iter;
    return issue_request<SendType>(iter, send_params, false, true);
}
template <uint8_t SendType, typename SendParams>
void PABotBase::issue_request(SendParams& send_params){
    std::map<uint64_t, PendingRequest>::iterator iter;
    issue_request<SendType>(iter, send_params, true, true);
}

template <
    uint8_t SendType, uint8_t RecvType,
    typename SendParams, typename RecvParams
>
void PABotBase::issue_and_wait(SendParams& send_params, RecvParams& recv_params){
    std::map<uint64_t, PendingRequest>::iterator iter;
    issue_request<SendType>(iter, send_params, true, false);

    AckState end_state = PABB_MSG_IS_COMMAND(SendType)
        ? AckState::FINISHED
        : AckState::ACKED;

    //  Wait for ack.
    std::unique_lock<std::mutex> lg(m_lock);
    while (iter->second.state != end_state){
        if (m_state.load(std::memory_order_acquire) != State::RUNNING){
            remove_request(iter);
            throw CancelledException();
        }
        m_cv.wait(lg);
    }

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


}

#endif
