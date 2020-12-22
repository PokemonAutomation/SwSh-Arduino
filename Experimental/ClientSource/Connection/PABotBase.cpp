/*  Pokemon Automation Bot Base
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include "Common/MessageProtocol.h"
#include "Common/PushButtons.h"
#include "Common/PokemonRoutines.h"
#include "PABotBase.h"

namespace PokemonAutomation{


PABotBase* global_connection = nullptr;


PABotBase::PABotBase(
    std::unique_ptr<StreamConnection> connection,
    std::chrono::milliseconds retransmit_delay
)
    : PABotBaseConnection(std::move(connection))
    , m_send_seq(1)
    , m_retransmit_delay(retransmit_delay)
{
    //  Send seqnum reset.
    pabb_MsgInfoSeqnumReset params;
    pabb_MsgAck response;
    send_request_and_wait<PABB_MSG_SEQNUM_RESET, PABB_MSG_ACK>(params, response);
}
////////////////////////////////////////////////////////////////////////////////
PABotBase::~PABotBase(){
    //  Must call this to stop the receiver thread from making any more async
    //  calls into this class which touch its fields.
    safely_stop();

    //  Now the receiver thread is dead. Nobody else is touching this class so
    //  it is safe to destruct.
}

uint8_t PABotBase::get_new_seqnum(){
    return m_send_seq++;
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
    auto iter = m_pending_requests.find(seqnum);
    if (iter == m_pending_requests.end()){
        log("Unexpected ack message: seqnum = " + std::to_string(seqnum));
        return;
    }
    if (iter->second.state == NOT_ACKED){
        iter->second.state = ACKED;
    }
    iter->second.message_type = type;
    iter->second.message_body = std::move(msg);
    iter->second.cv.notify_all();
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

    //  Now wake up the other thread.
    std::lock_guard<std::mutex> lg(m_lock);

    auto iter = m_pending_requests.find(params->seq_of_original_command);
    if (iter == m_pending_requests.end()){
        log(
            "Unexpected command finished message: seqnum = " + std::to_string(seqnum) +
            ", command_seqnum = " + std::to_string(params->seq_of_original_command)
        );
        return;
    }

    iter->second.state = FINISHED;
    iter->second.message_type = type;
    iter->second.message_body = std::move(msg);
    iter->second.cv.notify_all();
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

    case PABB_MSG_REQUEST_COMMAND_FINISHED:{
        process_command_finished<pabb_MsgRequestCommandFinished>(type, std::move(msg));
        return;
    }
    case PABB_MSG_REQUEST_COMMAND_FINISHED_I8:{
        process_command_finished<pabb_MsgRequestCommandFinishedI8>(type, std::move(msg));
        return;
    }
    case PABB_MSG_REQUEST_COMMAND_FINISHED_I16:{
        process_command_finished<pabb_MsgRequestCommandFinishedI16>(type, std::move(msg));
        return;
    }
    case PABB_MSG_REQUEST_COMMAND_FINISHED_I32:{
        process_command_finished<pabb_MsgRequestCommandFinishedI32>(type, std::move(msg));
        return;
    }
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
void PABotBase::set_leds(bool on){
    pabb_set_led params;
    params.on = on;
    pabb_MsgAck response;
    send_request_and_wait<PABB_MSG_REQUEST_SET_LED_STATE, PABB_MSG_ACK>(params, response);
}
void PABotBase::end_program_callback(){
    pabb_end_program_callback params;
    pabb_MsgAck response;
    send_request_and_wait<PABB_MSG_REQUEST_END_PROGRAM_CALLBACK, PABB_MSG_ACK>(params, response);
}



}
