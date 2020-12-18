/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include "Common/PokemonRoutines.h"
#include "Connection/PABotBase.h"


void resume_game_no_interact(bool tolerate_update_menu){
    resume_game_no_interact(*global_connection, tolerate_update_menu);
}
void resume_game_no_interact(PABotBase& device, bool tolerate_update_menu){
    pabb_resume_game_no_interact params;
    params.tolerate_update_menu = tolerate_update_menu;
    pabb_MsgRequestCommandFinished response;
    device.send_command_and_wait<PABB_MSG_COMMAND_RESUME_GAME_NO_INTERACT, PABB_MSG_REQUEST_COMMAND_FINISHED>(params, response);
}

void resume_game_back_out(bool tolerate_update_menu, uint16_t mash_B_time){
    resume_game_back_out(*global_connection, tolerate_update_menu, mash_B_time);
}
void resume_game_back_out(PABotBase& device, bool tolerate_update_menu, uint16_t mash_B_time){
    pabb_resume_game_back_out params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.mash_B_time = mash_B_time;
    pabb_MsgRequestCommandFinished response;
    device.send_command_and_wait<PABB_MSG_COMMAND_RESUME_GAME_BACK_OUT, PABB_MSG_REQUEST_COMMAND_FINISHED>(params, response);
}

void resume_game_front_of_den_nowatts(bool tolerate_update_menu){
    resume_game_front_of_den_nowatts(*global_connection, tolerate_update_menu);
}
void resume_game_front_of_den_nowatts(PABotBase& device, bool tolerate_update_menu){
    pabb_resume_game_front_of_den_nowatts params;
    params.tolerate_update_menu = tolerate_update_menu;
    pabb_MsgRequestCommandFinished response;
    device.send_command_and_wait<PABB_MSG_COMMAND_RESUME_GAME_FRONT_OF_DEN_NOWATTS, PABB_MSG_REQUEST_COMMAND_FINISHED>(params, response);
}

void reset_game_from_home(bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    reset_game_from_home(*global_connection, tolerate_update_menu, user_slot, game_slot2);
}
void reset_game_from_home(PABotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    pabb_reset_game_from_home params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.user_slot = user_slot;
    params.game_slot2 = game_slot2;
    pabb_MsgRequestCommandFinished response;
    device.send_command_and_wait<PABB_MSG_COMMAND_RESET_GAME_FROM_HOME, PABB_MSG_REQUEST_COMMAND_FINISHED>(params, response);
}
