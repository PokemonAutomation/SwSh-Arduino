/*  Pokemon Automation Bot Base
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include "CommonFramework/MessageProtocol.h"
#include "CommonFramework/PushButtons.h"
#include "CommonPokemon/PokemonRoutines.h"
#include "PABotBase.h"

namespace PokemonAutomation{


PABotBase* global_connection = nullptr;


PABotBase::PABotBase(
    std::unique_ptr<StreamConnection> connection,
    MessageLogger* logger,
    std::chrono::milliseconds retransmit_delay
)
    : PABotBaseConnection(std::move(connection))
    , m_send_seq(1)
    , m_retransmit_delay(retransmit_delay)
//    , m_active_wait(false)
    , m_stop(false)
    , m_sender_thread(&PABotBase::sender_thread, this)
{
    if (logger){
        add_message_snooper(*logger);
    }

    //  Send seqnum reset.
    pabb_MsgInfoSeqnumReset params;
    pabb_MsgAck response;
    send_request_and_wait<PABB_MSG_SEQNUM_RESET, PABB_MSG_ACK>(params, response);
}
////////////////////////////////////////////////////////////////////////////////
PABotBase::~PABotBase(){
    {
        std::lock_guard<std::mutex> lg(m_lock);
        m_stop.store(true, std::memory_order_release);
        m_cv.notify_all();
    }
    m_sender_thread.join();

    //  Must call this to stop the receiver thread from making any more async
    //  calls into this class which touch its fields.
    safely_stop();

    //  Now the receiver thread is dead. Nobody else is touching this class so
    //  it is safe to destruct.
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
        log("Ignoring message with invalid size.");
        return;
    }
    const Params* params = (const Params*)msg.c_str();
    uint8_t seqnum = params->seqnum;
    std::lock_guard<std::mutex> lg(m_lock);
    if (m_pending_requests.empty()){
        log("Unexpected ack message: seqnum = " + std::to_string(seqnum));
        return;
    }

    uint64_t full_seqnum = infer_full_seqnum(seqnum);
    auto iter = m_pending_requests.find(full_seqnum);
    if (iter == m_pending_requests.end()){
        log("Unexpected ack message: seqnum = " + std::to_string(seqnum));
        return;
    }

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
        log("Duplicate ack message: seqnum = " + std::to_string(seqnum));
        return;
    case AckState::FINISHED:
        log("Ack on command finish: seqnum = " + std::to_string(seqnum));
        return;
    }
}
template <typename Params>
void PABotBase::process_command_finished(uint8_t type, std::string msg){
    if (msg.size() != sizeof(Params)){
        log("Ignoring message with invalid size.");
        return;
    }
    const Params* params = (const Params*)msg.c_str();
    uint8_t seqnum = params->seqnum;

    //  Send the ack first.
    pabb_MsgAck ack;
    ack.seqnum = seqnum;
    send_message(PABB_MSG_ACK, std::string((char*)&ack, sizeof(ack)), false);

    std::lock_guard<std::mutex> lg(m_lock);
    if (m_pending_requests.empty()){
        log("Unexpected command finished message: seqnum = " + std::to_string(seqnum));
        return;
    }

    uint64_t full_seqnum = infer_full_seqnum(params->seq_of_original_command);
    auto iter = m_pending_requests.find(full_seqnum);
    if (iter == m_pending_requests.end()){
        log("Unexpected command finished message: seqnum = " + std::to_string(seqnum));
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
        log("Duplicate ack on command finish: seqnum = " + std::to_string(seqnum));
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
    auto last_sent = std::chrono::system_clock::now();
    while (!m_stop.load(std::memory_order_acquire)){
        std::unique_lock<std::mutex> lg(m_lock);

        auto now = std::chrono::system_clock::now();
        if (now - last_sent < m_retransmit_delay){
            m_cv.wait_for(lg, m_retransmit_delay);
            continue;
        }

//        std::cout << "sender_thread - m_pending_requests.size(): " << m_pending_requests.size() << std::endl;

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
}


uint32_t PABotBase::protocol_version(){
    pabb_MsgRequestProtocolVersion params;
    pabb_MsgAckI32 response;
    send_request_and_wait<PABB_MSG_REQUEST_PROTOCOL_VERSION, PABB_MSG_ACK_I32>(params, response);
    return response.data;
}
uint32_t PABotBase::program_version(){
    pabb_MsgRequestProgramVersion params;
    pabb_MsgAckI32 response;
    send_request_and_wait<PABB_MSG_REQUEST_PROGRAM_VERSION, PABB_MSG_ACK_I32>(params, response);
    return response.data;
}
uint8_t PABotBase::program_id(){
    pabb_MsgRequestProgramID params;
    pabb_MsgAckI8 response;
    send_request_and_wait<PABB_MSG_REQUEST_PROGRAM_ID, PABB_MSG_ACK_I8>(params, response);
    return response.data;
}
uint32_t PABotBase::system_clock(){
    pabb_system_clock params;
    pabb_MsgAckI32 response;
    send_request_and_wait<PABB_MSG_REQUEST_CLOCK, PABB_MSG_ACK_I32>(params, response);
    return response.data;
}
void PABotBase::end_program_callback(){
    pabb_end_program_callback params;
    pabb_MsgAck response;
    send_request_and_wait<PABB_MSG_REQUEST_END_PROGRAM_CALLBACK, PABB_MSG_ACK>(params, response);
}
void PABotBase::set_leds(bool on){
    pabb_MsgCommandSetLeds params;
    params.on = on;
    issue_request<PABB_MSG_COMMAND_SET_LED_STATE>(params);
}



}
