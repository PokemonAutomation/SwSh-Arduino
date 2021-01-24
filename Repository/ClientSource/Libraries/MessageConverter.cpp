/*  Message Pretty Printing
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <set>
#include <map>
#include <sstream>
#include "ClientSource/Libraries/Compiler.h"
#include "ClientSource/CommonFramework/MessageProtocol.h"
#include "ClientSource/CommonFramework/PushButtons.h"
#include "ClientSource/CommonPokemon/PokemonRoutines.h"
#include "ClientSource/CommonPokemon/PokemonProgramIDs.h"
#include "MessageConverter.h"

namespace PokemonAutomation{


std::map<uint8_t, MessageConverter>& converter_map(){
    static std::map<uint8_t, MessageConverter> converters;
    return converters;
}
void register_message_converter(uint8_t type, MessageConverter converter){
    std::map<uint8_t, MessageConverter>& converters = converter_map();
    auto iter = converters.find(type);
    if (iter != converters.end()){
        throw "Duplicate message type.";
    }
    converters[type] = converter;
}


int register_message_converters_framework_errors(){
    register_message_converter(
        PABB_MSG_ERROR_READY,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_READY - ";
            if (length != 0){ ss << "(invalid size)" << std::endl; return ss.str(); }
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_INVALID_MESSAGE,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_INVALID_MESSAGE - ";
            if (length != sizeof(pabb_MsgInfoInvalidMessage)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoInvalidMessage*)message;
            ss << "length = " << (unsigned)params->message_length;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_CHECKSUM_MISMATCH,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_CHECKSUM_MISMATCH - ";
            if (length != sizeof(pabb_MsgInfoChecksumMismatch)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoChecksumMismatch*)message;
            ss << "length = " << (unsigned)params->message_length;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_INVALID_TYPE,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_INVALID_TYPE - ";
            if (length != sizeof(pabb_MsgInfoInvalidType)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoInvalidType*)message;
            ss << "type = " << (unsigned)params->type;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_INVALID_REQUEST,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_INVALID_REQUEST - ";
            if (length != sizeof(pabb_MsgInfoInvalidRequest)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoInvalidRequest*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_MISSED_REQUEST,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_MISSED_REQUEST - ";
            if (length != sizeof(pabb_MsgInfoMissedRequest)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoMissedRequest*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_COMMAND_DROPPED,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_COMMAND_DROPPED - ";
            if (length != sizeof(pabb_MsgInfoCommandDropped)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoCommandDropped*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ERROR_WARNING,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ERROR_WARNING - ";
            if (length != sizeof(pabb_MsgInfoWARNING)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoWARNING*)message;
            ss << "error code = " << (unsigned)params->error_code;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_framework_acks(){
    register_message_converter(
        PABB_MSG_ACK,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ACK - ";
            if (length != sizeof(pabb_MsgAck)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgAck*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ACK_I8,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ACK_I8 - ";
            if (length != sizeof(pabb_MsgAckI8)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgAckI8*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", message = " << (unsigned)params->data;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ACK_I16,
        [](const char* message, size_t length){
            std::stringstream ss;
            if (length != sizeof(pabb_MsgAckI16)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgAckI16*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", message = " << (unsigned)params->data;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_ACK_I32,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_ACK_I32 - ";
            if (length != sizeof(pabb_MsgAckI32)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgAckI32*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", message = " << params->data;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_framework_requests(){
    register_message_converter(
        PABB_MSG_SEQNUM_RESET,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_SEQNUM_RESET - ";
            if (length != sizeof(pabb_MsgInfoSeqnumReset)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoSeqnumReset*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_REQUEST_PROTOCOL_VERSION,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_REQUEST_PROTOCOL_VERSION - ";
            if (length != sizeof(pabb_MsgRequestProtocolVersion)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgRequestProtocolVersion*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_REQUEST_PROGRAM_VERSION,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_REQUEST_PROGRAM_VERSION - ";
            if (length != sizeof(pabb_MsgRequestProgramVersion)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgRequestProgramVersion*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_REQUEST_PROGRAM_ID,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_REQUEST_PROGRAM_ID - ";
            if (length != sizeof(pabb_MsgRequestProgramID)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgRequestProgramID*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_REQUEST_CLOCK,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_REQUEST_CLOCK - ";
            if (length != sizeof(pabb_system_clock)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_system_clock*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_REQUEST_END_PROGRAM_CALLBACK,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "end_program_callback() - ";
            if (length != sizeof(pabb_end_program_callback)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_end_program_callback*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_REQUEST_COMMAND_FINISHED,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_REQUEST_COMMAND_FINISHED - ";
            if (length != sizeof(pabb_MsgRequestCommandFinished)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgRequestCommandFinished*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", seq_of_original_command = " << (unsigned)params->seq_of_original_command;
            ss << ", finish_time = " << params->finish_time;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_SET_LED_STATE,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_COMMAND_SET_LED_STATE - ";
            if (length != sizeof(pabb_MsgCommandSetLeds)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgCommandSetLeds*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", on = " << params->on;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_custom_info(){
    register_message_converter(
        PABB_MSG_INFO_I32,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "PABB_MSG_INFO_I32 - ";
            if (length != sizeof(pabb_MsgInfoI32)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_MsgInfoI32*)message;
            ss << "tag = " << (unsigned)params->tag;
            ss << ", data = " << params->data;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_push_button_framework(){
    register_message_converter(
        PABB_MSG_COMMAND_PBF_WAIT,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "pbf_wait() - ";
            if (length != sizeof(pabb_pbf_wait)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_pbf_wait*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", ticks = " << params->ticks;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_PBF_PRESS_BUTTON,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "pbf_press_button() - ";
            if (length != sizeof(pabb_pbf_press_button)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_pbf_press_button*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", button = " << params->button;
            ss << ", hold_ticks = " << params->hold_ticks;
            ss << ", release_ticks = " << params->release_ticks;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_PBF_PRESS_DPAD,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "pbf_press_dpad() - ";
            if (length != sizeof(pabb_pbf_press_dpad)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_pbf_press_dpad*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", dpad = " << (unsigned)params->dpad;
            ss << ", hold_ticks = " << params->hold_ticks;
            ss << ", release_ticks = " << params->release_ticks;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_PBF_MOVE_JOYSTICK_L,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "pbf_move_left_joystick - ";
            if (length != sizeof(pabb_pbf_move_joystick)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_pbf_move_joystick*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", x = " << (unsigned)params->x;
            ss << ", y = " << (unsigned)params->y;
            ss << ", hold_ticks = " << params->hold_ticks;
            ss << ", release_ticks = " << params->release_ticks;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_PBF_MOVE_JOYSTICK_R,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "pbf_move_right_joystick() - ";
            if (length != sizeof(pabb_pbf_move_joystick)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_pbf_move_joystick*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", x = " << (unsigned)params->x;
            ss << ", y = " << (unsigned)params->y;
            ss << ", hold_ticks = " << params->hold_ticks;
            ss << ", release_ticks = " << params->release_ticks;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_MASH_BUTTON,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "pbf_mash_button() - ";
            if (length != sizeof(pabb_pbf_mash_button)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_pbf_mash_button*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", button = " << params->button;
            ss << ", ticks = " << params->ticks;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_pokemon_den_entry(){
    register_message_converter(
        PABB_MSG_COMMAND_RESET_GAME_FROM_HOME,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "reset_game_from_home() - ";
            if (length != sizeof(pabb_reset_game_from_home)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_reset_game_from_home*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", tolerate_update_menu = " << params->tolerate_update_menu;
            ss << ", user_slot = " << params->user_slot;
            ss << ", game_slot2 = " << params->game_slot2;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "settings_to_enter_game_den_lobby() - ";
            if (length != sizeof(pabb_settings_to_enter_game_den_lobby)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_settings_to_enter_game_den_lobby*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", tolerate_update_menu = " << params->tolerate_update_menu;
            ss << ", fast = " << params->fast;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_START_GAME_FROM_HOME,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "start_game_from_home() - ";
            if (length != sizeof(pabb_start_game_from_home)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_start_game_from_home*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", tolerate_update_menu = " << params->tolerate_update_menu;
            ss << ", game_slot = " << (unsigned)params->game_slot;
            ss << ", user_slot = " << (unsigned)params->user_slot;
            ss << ", backup_save = " << params->backup_save;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_CLOSE_GAME,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "close_game() - ";
            if (length != sizeof(pabb_close_game)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_close_game*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_pokemon_date_spam(){
    register_message_converter(
        PABB_MSG_COMMAND_HOME_TO_DATE_TIME,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "home_to_date_time() - ";
            if (length != sizeof(pabb_home_to_date_time)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_home_to_date_time*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", fast = " << params->fast;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "roll_date_forward_1() - ";
            if (length != sizeof(pabb_roll_date_forward_1)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_roll_date_forward_1*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", fast = " << params->fast;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "roll_date_backward_N() - ";
            if (length != sizeof(pabb_roll_date_backward_N)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_roll_date_backward_N*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", skips = " << (unsigned)params->skips;
            ss << ", fast = " << params->fast;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "home_roll_date_enter_game() - ";
            if (length != sizeof(pabb_home_roll_date_enter_game)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_home_roll_date_enter_game*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            ss << ", rollback_year = " << params->rollback_year;
            return ss.str();
        }
    );
    register_message_converter(
        PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "home_roll_date_enter_game_autorollback() - ";
            if (length != sizeof(pabb_touch_date_from_home)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_touch_date_from_home*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            return ss.str();
        }
    );
    return 0;
}
int register_message_converters_pokemon_other(){
    register_message_converter(
        PABB_MSG_COMMAND_ENTER_8DIGITS,
        [](const char* message, size_t length){
            std::stringstream ss;
            ss << "enter_8digits() - ";
            if (length != sizeof(pabb_enter_8digits)){ ss << "(invalid size)" << std::endl; return ss.str(); }
            const auto* params = (const pabb_enter_8digits*)message;
            ss << "seqnum = " << (unsigned)params->seqnum;
            uint8_t digits[8];
            digits[0] = params->digit01 & 0xf;
            digits[1] = params->digit01 >> 4;
            digits[2] = params->digit23 & 0xf;
            digits[3] = params->digit23 >> 4;
            digits[4] = params->digit45 & 0xf;
            digits[5] = params->digit45 >> 4;
            digits[6] = params->digit67 & 0xf;
            digits[7] = params->digit67 >> 4;
            ss << ", digits = "
                << (int)digits[0]
                << (int)digits[1]
                << (int)digits[2]
                << (int)digits[3]
                << (int)digits[4]
                << (int)digits[5]
                << (int)digits[6]
                << (int)digits[7];
            return ss.str();
        }
    );
    return 0;
}

int init_MessageLogger =
    register_message_converters_framework_errors() +
    register_message_converters_framework_acks() +
    register_message_converters_framework_requests() +
    register_message_converters_custom_info() +
    register_message_converters_push_button_framework() +
    register_message_converters_pokemon_den_entry() +
    register_message_converters_pokemon_date_spam() +
    register_message_converters_pokemon_other();


std::string message_to_string(uint8_t type, const std::string& message){
    return message_to_string(type, message.c_str(), message.size());
}
std::string message_to_string(uint8_t type, const char* message, size_t length){
    const std::map<uint8_t, MessageConverter>& converters = converter_map();
    auto iter = converters.find(type);
    if (iter == converters.end()){
        std::stringstream ss;
        ss << "Unknown Message Type " << (unsigned)type << ": length = " << length;
        return ss.str();
    }
    return iter->second(message, length);
}


std::string program_name(uint8_t id){
    switch (id){
    case PABB_PID_UNSPECIFIED:              return "Unspecified/Unknown";
    case PABB_PID_PABOTBASE:                return "PABotBase";
    case PABB_PID_CUSTOM_PROGRAM:           return "Custom Program";
    case PABB_PID_SANDBOX:                  return "Sandbox";

    case PABB_PID_TURBOA:                   return "TurboA";
    case PABB_PID_MASS_RELEASE:             return "MassRelease";
    case PABB_PID_FAST_CODE_ENTRY:          return "FastCodeEntry";
    case PABB_PID_SURPRISE_TRADE:           return "SurpriseTrade";
    case PABB_PID_TRADE_BOT:                return "TradeBot";
    case PABB_PID_CLOTHING_BUYER:           return "ClothingBuyer";
    case PABB_PID_BALL_THROWER:             return "BallThrower";

    case PABB_PID_DATESPAM_WATT_FARMER:             return "DateSpam-WattFarmer";
    case PABB_PID_DATESPAM_BERRY_FARMER:            return "DateSpam-BerryFarmer";
    case PABB_PID_DATESPAM_LOTO_FARMER:             return "DateSpam-LotoFarmer";
    case PABB_PID_DATESPAM_STOW_ON_SIDE_FARMER:     return "DateSpam-StowOnSideFarmer";
    case PABB_PID_DATESPAM_DAILY_HIGHLIGHT_FARMER:  return "DateSpam-DailyHighlightFarmer";

    case PABB_PID_MULTIGAME_FOSSIL:                         return "MultiGameFossil";
    case PABB_PID_SHINYHUNT_REGI:                           return "ShinyHunt-Regi";
    case PABB_PID_SHINYHUNT_SWORDS_OF_JUSTICE:              return "ShinyHunt-SwordsOfJustice";
    case PABB_PID_SHINYHUNT_UNATTENDED_REGI:                return "ShinyHuntUnattended-Regi";
    case PABB_PID_SHINYHUNT_UNATTENDED_SWORDS_OF_JUSTICE:   return "ShinyHuntUnattended-SwordsOfJustice";
    case PABB_PID_SHINYHUNT_UNATTENDED_STRONG_SPAWN:        return "ShinyHuntUnattended-StrongSpawn";
    case PABB_PID_SHINYHUNT_UNATTENDED_REGIGIGAS:           return "ShinyHuntUnattended-Regigigas";
    case PABB_PID_SHINYHUNT_UNATTENDED_REGIGIGAS2:          return "ShinyHuntUnattended-Regigigas2";
    case PABB_PID_SHINYHUNT_UNATTENDED_IOA_TRADE:           return "ShinyHuntUnattended-IoATrade";

    case PABB_PID_BEAM_RESET:               return "BeamReset";
    case PABB_PID_EVENT_BEAM_FINDER:        return "EventBeamFinder";
    case PABB_PID_DAYSKIPPER_JPN:           return "DaySkipperJPN";
    case PABB_PID_DAYSKIPPER_EU:            return "DaySkipperEU";
    case PABB_PID_DAYSKIPPER_US:            return "DaySkipperUS";
    case PABB_PID_DAYSKIPPER_JPN_7P8K:      return "DaySkipperJPN-7.8k";

    case PABB_PID_FRIEND_DELETE:            return "FriendDelete";
    case PABB_PID_DEN_ROLLER:               return "DenRoller";
    case PABB_PID_AUTOHOST_ROLLING:         return "AutoHost-Rolling";
    case PABB_PID_AUTOHOST_MULTIGAME:       return "AutoHost-MultiGame";

    case PABB_PID_EGG_FETCHER2:             return "EggFetcher2";
    case PABB_PID_EGG_HATCHER:              return "EggHatcher";
    case PABB_PID_EGG_COMBINED2:            return "EggCombined2";
    case PABB_PID_EGG_SUPER_COMBINED2:      return "EggSuperCombined2";
    case PABB_PID_GOD_EGG_ITEM_DUPE:        return "GodEggItemDupe";
    case PABB_PID_GOD_EGG_DUPLICATION:      return "GodEggDuplication";

    default: return "Unknown ID";
    }
}




}

