/*  Message Protocol
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 * 
 *      Pokemon Automation Bot-Base implements reliable data transmissions over
 *  serial communication. This is done by checksumming messages along with a
 *  protocol that is tolerance to data drops.
 * 
 *  This file describes the message protocol. The data being transmitted is raw
 *  binary and not is readable text.
 * 
 * 
 *  Message Format:
 *      byte 0: Length of the entire message. (bits are inverted)
 *      byte 1: Message Type
 *      byte X: Optional data of variable length.
 *      Last 4 bytes: CRC32C of the entire message except these last 4 bytes.
 * 
 *      Thus there are 6 bytes of overhead for each message.
 * 
 * 
 *  There are currently 4 categories of message types:
 * 
 *      1.  Info: These are simple one-way messages. They do not need need to be
 *          acked and may be dropped without adversely affecting anything.
 * 
 *      2.  Ack/Response: These are messages sent in response to an earlier
 *          message that was received.
 * 
 *      3.  Request: The sender requests the receiver to do something simple.
 *          The receiver must respond with an ack.
 * 
 *          This is used for things that take no clock time. For example, querying
 *          for program identifiers, turning on/off LEDs, or setting flags in the
 *          program to change its behavior in the future.
 * 
 *      4.  Command: The sender requests the receiver to do a large asynchronous
 *          operation. The receiver must ack this message. Once the command is
 *          finished, the receiver must send a request message back to the sender
 *          to indicate that the command is finished.
 * 
 *          This is used for issuing button presses or other subroutines that
 *          consume time.
 * 
 * 
 *  General Protocol:
 * 
 *      1.  Every time you send a new request/command message, you increment
 *          your sequence number (seqnum) by 1.
 * 
 *      2.  If you receive an invalid message (bad length or bad checksum), ignore
 *          the first byte and attempt to parse the next byte as the start of a
 *          new message.
 * 
 *      3.  If you receive a zero for the 1st byte of a message, ignore it and
 *          attempt to parse the next byte as the start of a new message.
 * 
 *      4.  At any point, you can send a bunch of zero bytes. This will cause
 *          the receiver to re-synchronize.
 * 
 *      5.  If you receive a request/command message, you must send the appropriate
 *          ack/response message using the same seqnum.
 * 
 *      6.  If you send a request/command message and don't get a response after
 *          a time limit, you should resend the message with the same seqnum.
 * 
 *      7.  If you receive a duplicate request/command message, ack/respond to it,
 *          but don't actually process the request again. (idempotency)
 * 
 *      8.  If you receive a command message, you must first ack the message itself.
 *          Once the command is finished, you must send a request referencing the
 *          command to indicate that it is finished. You will receive an ack for
 *          this short (finishing) command, and if you don't, send it again until
 *          you do.
 * 
 * 
 *  Failure Analysis:
 * 
 *      -   Corrupted messages will either fail checksum or will have an invalid
 *          length/type. These are simply ignored and dropped.
 * 
 *      -   If either sender or receiver gets out-of-sync and loses track of
 *          message boundaries, it will eventually find the boundary again by
 *          simply trying to parse every byte as the start of a new message and
 *          verifying the length and CRC.
 * 
 *      -   If a request/command is dropped, no ack will be received. The sender
 *          will eventually send the command again. (#6)
 * 
 *      -   If an ack is dropped, the sender will eventually resend the
 *          request/command again. The receiver will see the duplicate
 *          request/command and ack it. But the receiver will not process it
 *          again to preserve idempotency. (#7)
 * 
 *  The current protocol guarantees that all requests and commands be processed
 *  exactly once. If ordering is important, then the sender should never issue
 *  another request/command before the previous when is acked and finished.
 * 
 * 
 *  PABotBase Specifics:
 * 
 *      -   PABotBase does not allow concurrent commands. If it receives a
 *          command while one is already running, it drops it and responds
 *          with "PABB_MSG_INFO_COMMAND_DROPPED". (Any command that results
 *          in a button press or a wait is a long command.)
 * 
 *      -   PABotBase can still handle other messages while it is running a long
 *          command.
 * 
 */

#ifndef PokemonAutomation_MessageProtocol_H
#define PokemonAutomation_MessageProtocol_H

#include <stdbool.h>
#include <stdint.h>
#include "ControllerDefs.h"

#if _WIN32
#pragma pack(push, 1)
#define PABB_PACK
#else
#define PABB_PACK   __attribute__((packed))
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define PABB_PROTOCOL_VERSION       20201217
#define PABB_PROGRAM_VERSION        2020121703

#define PABB_BAUD_RATE              115200
#define PABB_RETRANSMIT_DELAY       25

#define PABB_MAX_MESSAGE_SIZE       14
#define SERIAL_MESSAGE_OVERHEAD     (2 + sizeof(uint32_t))

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Basic Message Types

////////////////////////////////////////////////////////////////////////////////
//  Info
#define PABB_MSG_INFO_READY                     0x00
//  No Parameters

#define PABB_MSG_INFO_INVALID_MESSAGE           0x01
typedef struct{
    uint8_t message_length;
} PABB_PACK pabb_MsgInfoInvalidMessage;

#define PABB_MSG_INFO_CHECKSUM_MISMATCH         0x02
typedef struct{
    uint8_t message_length;
} PABB_PACK pabb_MsgInfoChecksumMismatch;

#define PABB_MSG_INFO_INVALID_TYPE              0x03
typedef struct{
    uint8_t type;
} PABB_PACK pabb_MsgInfoInvalidType;

#define PABB_MSG_INFO_INVALID_REQUEST           0x04
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_MsgInfoInvalidRequest;

#define PABB_MSG_INFO_COMMAND_DROPPED           0x05
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_MsgInfoCommandDropped;

#define PABB_MSG_INFO_WARNING                   0x06
typedef struct{
    uint16_t error_code;
} PABB_PACK pabb_MsgInfoWARNING;

#define PABB_MSG_INFO_I32                       0x07
typedef struct{
    uint32_t data;
} PABB_PACK pabb_MsgInfoI32;

////////////////////////////////////////////////////////////////////////////////
//  Ack/Response
#define PABB_MSG_ACK                            0x10
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_MsgAck;

#define PABB_MSG_ACK_I8                         0x11
typedef struct{
    uint8_t seqnum;
    uint8_t data;
} PABB_PACK pabb_MsgAckI8;

#define PABB_MSG_ACK_I16                        0x12
typedef struct{
    uint8_t seqnum;
    uint16_t data;
} PABB_PACK pabb_MsgAckI16;

#define PABB_MSG_ACK_I32                        0x13
typedef struct{
    uint8_t seqnum;
    uint32_t data;
} PABB_PACK pabb_MsgAckI32;

#define PABB_MSG_REQUEST_COMMAND_FINISHED       0x18
typedef struct{
    uint8_t seqnum;
    uint8_t seq_of_original_command;
} PABB_PACK pabb_MsgRequestCommandFinished;

#define PABB_MSG_REQUEST_COMMAND_FINISHED_I8    0x19
typedef struct{
    uint8_t seqnum;
    uint8_t seq_of_original_command;
    uint8_t return_value;
} PABB_PACK pabb_MsgRequestCommandFinishedI8;

#define PABB_MSG_REQUEST_COMMAND_FINISHED_I16   0x1a
typedef struct{
    uint8_t seqnum;
    uint8_t seq_of_original_command;
    uint16_t return_value;
} PABB_PACK pabb_MsgRequestCommandFinishedI16;

#define PABB_MSG_REQUEST_COMMAND_FINISHED_I32   0x1b
typedef struct{
    uint8_t seqnum;
    uint8_t seq_of_original_command;
    uint32_t return_value;
} PABB_PACK pabb_MsgRequestCommandFinishedI32;

////////////////////////////////////////////////////////////////////////////////
//  Requests
#define PABB_MSG_REQUEST_PROTOCOL_VERSION       0x20
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_MsgRequestProtocolVersion;

#define PABB_MSG_REQUEST_PROGRAM_VERSION        0x21
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_MsgRequestProgramVersion;

#define PABB_MSG_REQUEST_PROGRAM_ID             0x22
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_MsgRequestProgramID;

#define PABB_MSG_REQUEST_CLOCK                  0x23
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_system_clock;

#define PABB_MSG_REQUEST_SET_LED_STATE          0x24
typedef struct{
    uint8_t seqnum;
    bool on;
} PABB_PACK pabb_set_led;

#define PABB_MSG_REQUEST_END_PROGRAM_CALLBACK   0x25
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_end_program_callback;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if _WIN32
#pragma pack(pop)
#endif

#endif
