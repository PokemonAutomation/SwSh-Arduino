/*  Pokemon Automation Bot Base
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include <emmintrin.h>
#include "Common/DeviceFramework/MessageProtocol.h"
#include "Common/DeviceFramework/PushButtons.h"
#include "Common/Pokemon/PokemonRoutines.h"
#include "Common/Pokemon/PokemonProgramIDs.h"
#include "PABotBase.h"

////////////////////////////////////////////////////////////////////////////////
namespace PokemonAutomation{





PABotBase::PABotBase(
    std::unique_ptr<StreamConnection> connection,
    MessageLogger* logger,
    std::chrono::milliseconds retransmit_delay
)
    : PABotBaseConnection(std::move(connection))
    , m_send_seq(1)
    , m_retransmit_delay(retransmit_delay)
    , m_last_ack(std::chrono::system_clock::now())
    , m_state(State::RUNNING)
    , m_sender_thread(&PABotBase::sender_thread, this)
{
    set_sniffer(logger);
}
PABotBase::~PABotBase(){
    stop();
    while (m_state.load(std::memory_order_acquire) != State::STOPPED){
        _mm_pause();
    }
}
void PABotBase::connect(){
    //  Send seqnum reset.
    pabb_MsgInfoSeqnumReset params;
    pabb_MsgAck response;
    issue_and_wait<PABB_MSG_SEQNUM_RESET, PABB_MSG_ACK>(params, response);
}
void PABotBase::stop(){
//    cout << "stop" << endl;

    //  Make sure only one thread can get in here.
    State expected = State::RUNNING;
    if (!m_state.compare_exchange_strong(expected, State::NO_COMMANDS)){
        return;
    }

    //  Send a stop request, but don't wait for a response that we may never
    //  receive.
    pabb_MsgRequestStop params;
    try_issue_request<PABB_MSG_REQUEST_STOP>(params);
    m_state.store(State::STOPPING, std::memory_order_release);

    //  Wake everyone up.
    {
        std::lock_guard<std::mutex> lg(m_lock);
        m_cv.notify_all();
    }
    m_sender_thread.join();

    //  Must call this to stop the receiver thread from making any more async
    //  calls into this class which touch its fields.
    safely_stop();

    //  Now the receiver thread is dead. Nobody else is touching this class so
    //  it is safe to destruct.
    m_state.store(State::STOPPED, std::memory_order_release);
}

void PABotBase::wait_for_all_requests(){
    std::unique_lock<std::mutex> lg(m_lock);
//    m_active_wait = true;
    m_cv.wait(lg, [&]{ return m_pending_requests.empty(); });
//    m_active_wait = false;
}
void PABotBase::remove_request(std::map<uint64_t, PendingRequest>::iterator iter){
    //  Must be called under the lock.
    m_pending_requests.erase(iter);
//    if (m_active_wait && m_pending_requests.empty()){
        m_cv.notify_all();
//    }
}
uint64_t PABotBase::infer_full_seqnum(uint8_t seqnum) const{
    //  The protocol uses an 8-bit seqnum that wraps around. For our purposes of
    //  retransmits, we use a full 64-bit seqnum to maintain sorting order
    //  across the wrap-arounds.

    //  Since the oldest unacked messaged will never be more than 63 (MAX_SEQNUM_GAP)
    //  requests old, there is no ambiguity on which request is being referred
    //  to with just the lower 8 bits.
    //  Here we infer the upper 56 bits of the seqnum to obtain the full 64-bit
    //  seqnum that we need to index our map.

    //  This needs to be called inside the lock. Furthermore, the map must not
    //  be empty. If it is empty, we know we don't have it and can drop it
    //  before we even call this function.

    //  Figure out the upper 56 bits of the seqnum.
    uint64_t lo = m_pending_requests.begin()->first;
    uint64_t hi = m_pending_requests.rbegin()->first;
    uint64_t lo_candidate = (lo & 0xffffffffffffff00) | seqnum;
    uint64_t hi_candidate = (hi & 0xffffffffffffff00) | seqnum;
    return lo_candidate >= lo
        ? lo_candidate
        : hi_candidate;
}

template <typename Params>
void PABotBase::process_ack(uint8_t type, std::string msg){
    if (msg.size() != sizeof(Params)){
        m_sniffer->log("Ignoring message with invalid size.");
        return;
    }
    const Params* params = (const Params*)msg.c_str();
    uint8_t seqnum = params->seqnum;
    std::lock_guard<std::mutex> lg(m_lock);
    if (m_pending_requests.empty()){
        m_sniffer->log("Unexpected ack message: seqnum = " + std::to_string(seqnum));
        return;
    }

    uint64_t full_seqnum = infer_full_seqnum(seqnum);
    auto iter = m_pending_requests.find(full_seqnum);
    if (iter == m_pending_requests.end()){
        m_sniffer->log("Unexpected ack message: seqnum = " + std::to_string(seqnum));
        return;
    }

    m_last_ack.store(std::chrono::system_clock::now(), std::memory_order_release);

    switch (iter->second.state){
    case AckState::NOT_ACKED:
//        std::cout << "acked: " << full_seqnum << std::endl;
        iter->second.state = AckState::ACKED;
        iter->second.ack_type = type;
        iter->second.ack_body = std::move(msg);
        if (iter->second.is_command){
//            std::cout << "acked command: " << full_seqnum << std::endl;
            return;
        }
        if (iter->second.silent_remove){
            remove_request(iter);
        }else{
//            std::cout << "notify()" << std::endl;
            m_cv.notify_all();
        }
        return;
    case AckState::ACKED:
        m_sniffer->log("Duplicate ack message: seqnum = " + std::to_string(seqnum));
        return;
    case AckState::FINISHED:
        m_sniffer->log("Ack on command finish: seqnum = " + std::to_string(seqnum));
        return;
    }
}
template <typename Params>
void PABotBase::process_command_finished(uint8_t type, std::string msg){
    if (msg.size() != sizeof(Params)){
        m_sniffer->log("Ignoring message with invalid size.");
        return;
    }
    const Params* params = (const Params*)msg.c_str();
    uint8_t seqnum = params->seqnum;
    uint8_t command_seqnum = params->seq_of_original_command;

    //  Send the ack first.
    pabb_MsgAck ack;
    ack.seqnum = seqnum;
    send_message(PABB_MSG_ACK, std::string((char*)&ack, sizeof(ack)), false);

    std::lock_guard<std::mutex> lg(m_lock);
    if (m_pending_requests.empty()){
        m_sniffer->log(
            "Unexpected command finished message: seqnum = " + std::to_string(seqnum) +
            ", command_seqnum = " + std::to_string(command_seqnum)
        );
        return;
    }

    uint64_t full_seqnum = infer_full_seqnum(command_seqnum);
    auto iter = m_pending_requests.find(full_seqnum);
    if (iter == m_pending_requests.end()){
        m_sniffer->log(
            "Unexpected command finished message: seqnum = " + std::to_string(seqnum) +
            ", command_seqnum = " + std::to_string(command_seqnum)
        );
        return;
    }

    switch (iter->second.state){
    case AckState::NOT_ACKED:
    case AckState::ACKED:
        if (iter->second.silent_remove){
            remove_request(iter);
        }else{
            iter->second.state = AckState::FINISHED;
            iter->second.ack_type = type;
            iter->second.ack_body = std::move(msg);
            m_cv.notify_all();
        }
        return;
    case AckState::FINISHED:
        m_sniffer->log("Duplicate ack on command finish: seqnum = " + std::to_string(seqnum));
        return;
    }
}
void PABotBase::on_recv_message(uint8_t type, std::string msg){
    switch (type){
    case PABB_MSG_ACK:
        process_ack<pabb_MsgAck>(type, std::move(msg));
        return;
    case PABB_MSG_ACK_I8:
        process_ack<pabb_MsgAckI8>(type, std::move(msg));
        return;
    case PABB_MSG_ACK_I16:
        process_ack<pabb_MsgAckI16>(type, std::move(msg));
        return;
    case PABB_MSG_ACK_I32:
        process_ack<pabb_MsgAckI32>(type, std::move(msg));
        return;
//    case PABB_MSG_INFO_COMMAND_DROPPED:
//        return;

    case PABB_MSG_REQUEST_COMMAND_FINISHED:{
        process_command_finished<pabb_MsgRequestCommandFinished>(type, std::move(msg));
        return;
    }
    }
}

void PABotBase::sender_thread(){
//    cout << "sender_thread()" << endl;
    auto last_sent = std::chrono::system_clock::now();
    while (m_state.load(std::memory_order_acquire) == State::RUNNING){
        std::unique_lock<std::mutex> lg(m_lock);

        auto now = std::chrono::system_clock::now();
        if (now - last_sent < m_retransmit_delay){
            m_cv.wait_for(lg, m_retransmit_delay);
            continue;
        }

//        std::cout << "sender_thread - m_pending_requests.size(): " << m_pending_requests.size() << std::endl;
//        cout << "m_pending_requests.size()" << endl;

        //  Retransmit
        //      Iterate through all pending requests and retransmit them in
        //  chronological order. Skip the ones that are new.
        for (auto iter : m_pending_requests){
            if (
                iter.second.state == AckState::NOT_ACKED &&
                std::chrono::system_clock::now() - iter.second.first_sent >= m_retransmit_delay
            ){
                send_message(iter.second.message_type, iter.second.message_body, true);
            }
        }
        last_sent = std::chrono::system_clock::now();
    }
//    cout << "sender_thread() - exit" << endl;
}




bool PABotBase::try_issue_request_unprotected(
    std::map<uint64_t, PendingRequest>::iterator& iter,
    uint8_t send_type, char* send_params, size_t send_bytes,
    bool silent_remove, size_t queue_limit
){
    State state = m_state.load(std::memory_order_acquire);
    if (state == State::STOPPING){
        throw CancelledException();
    }

    bool is_command = PABB_MSG_IS_COMMAND(send_type);
    if (state == State::NO_COMMANDS && is_command){
        throw CancelledException();
    }

    //  Command queue is full.
    if (is_command && m_pending_requests.size() >= queue_limit){
//        cout << "Command queue is full" << endl;
        return false;
    }

    //  Too many pending requests.
    if (m_pending_requests.size() >= MAX_SEQNUM_GAP){
        return false;
    }

    uint64_t seqnum = m_send_seq;

//    //  Oldest outstanding message is too old.
//    if (!m_pending_requests.empty() && seqnum - m_pending_requests.begin()->first >= MAX_SEQNUM_GAP){
//        cout << "Outstanding too old: seqnum = " << seqnum << ", oldest = " << m_pending_requests.begin()->first << endl;
//        return false;
//    }

    send_params[0] = (uint8_t)seqnum;

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
    handle->is_command = PABB_MSG_IS_COMMAND(send_type);
    handle->silent_remove = silent_remove;
    handle->message_type = send_type;
    handle->message_body = std::string(send_params, send_bytes);
    handle->first_sent = std::chrono::system_clock::now();

    //  Send message.
    send_message(send_type, handle->message_body, false);
//    handle->last_sent = std::chrono::system_clock::now();

    iter = ret.first;
    return true;
}
bool PABotBase::issue_request(
    std::map<uint64_t, PendingRequest>::iterator& iter,
    uint8_t send_type, char* send_params, size_t send_bytes,
    bool silent_remove
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
    if (send_bytes > PABB_MAX_MESSAGE_SIZE){
        throw "Message is too long.";
    }

    std::unique_lock<std::mutex> lg(m_lock);
    while (true){
        if (try_issue_request_unprotected(
            iter,
            send_type, send_params, send_bytes,
            silent_remove, MAX_PENDING_REQUESTS
        )){
            return true;
        }
        m_cv.wait(lg);
    }
}


bool PABotBase::try_issue_request(
    uint8_t send_type, char* send_params, size_t send_bytes
){
    std::map<uint64_t, PendingRequest>::iterator iter;
    std::lock_guard<std::mutex> lg(m_lock);
    return try_issue_request_unprotected(iter, send_type, send_params, send_bytes, true, MAX_PENDING_REQUESTS);
}
void PABotBase::issue_request(
    uint8_t send_type, char* send_params, size_t send_bytes
){
    std::map<uint64_t, PendingRequest>::iterator iter;
    issue_request(iter, send_type, send_params, send_bytes, true);
}
void PABotBase::issue_and_wait(
    uint8_t send_type, char* send_params, size_t send_bytes,
    uint8_t recv_type, char* recv_params, size_t recv_bytes
){
    std::map<uint64_t, PendingRequest>::iterator iter;
//    issue_request<SendType>(iter, send_params, true, false);
    issue_request(iter, send_type, send_params, send_bytes, false);

    const bool is_command = PABB_MSG_IS_COMMAND(send_type);
    AckState end_state = is_command
        ? AckState::FINISHED
        : AckState::ACKED;

    //  Wait for ack.
    std::unique_lock<std::mutex> lg(m_lock);
    while (iter->second.state != end_state){
        State state = m_state.load(std::memory_order_acquire);
        if (state == State::STOPPING){
            remove_request(iter);
            throw CancelledException();
        }
        if (state == State::NO_COMMANDS && is_command){
            remove_request(iter);
            throw CancelledException();
        }
        m_cv.wait(lg);
    }

    //  Verify return payload.
    uint8_t type = iter->second.ack_type;
    if (type != recv_type){
        throw "Received incorrect response type: " + std::to_string(type);
    }
    const std::string& body = iter->second.ack_body;
    if (body.size() != recv_bytes){
        throw "Received incorrect response size: " + std::to_string(body.size());
    }
    memcpy(recv_params, body.c_str(), body.size());
    remove_request(iter);
}




uint32_t PABotBase::protocol_version(){
    pabb_MsgRequestProtocolVersion params;
    pabb_MsgAckI32 response;
    issue_and_wait<PABB_MSG_REQUEST_PROTOCOL_VERSION, PABB_MSG_ACK_I32>(params, response);
    return response.data;
}
uint32_t PABotBase::program_version(){
    pabb_MsgRequestProgramVersion params;
    pabb_MsgAckI32 response;
    issue_and_wait<PABB_MSG_REQUEST_PROGRAM_VERSION, PABB_MSG_ACK_I32>(params, response);
    return response.data;
}
uint8_t PABotBase::program_id(){
    pabb_MsgRequestProgramID params;
    pabb_MsgAckI8 response;
    issue_and_wait<PABB_MSG_REQUEST_PROGRAM_ID, PABB_MSG_ACK_I8>(params, response);
    return response.data;
}



}
