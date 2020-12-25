/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include "Common/PokemonRoutines.h"
#include "Connection/PABotBase.h"

using namespace PokemonAutomation;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Game Entry
void resume_game_no_interact(bool tolerate_update_menu){
    resume_game_no_interact(*global_connection, tolerate_update_menu);
}
void resume_game_no_interact(PABotBase& device, bool tolerate_update_menu){
    pabb_resume_game_no_interact params;
    params.tolerate_update_menu = tolerate_update_menu;
    device.issue_request<PABB_MSG_COMMAND_RESUME_GAME_NO_INTERACT>(params);
}

void resume_game_back_out(bool tolerate_update_menu, uint16_t mash_B_time){
    resume_game_back_out(*global_connection, tolerate_update_menu, mash_B_time);
}
void resume_game_back_out(PABotBase& device, bool tolerate_update_menu, uint16_t mash_B_time){
    pabb_resume_game_back_out params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.mash_B_time = mash_B_time;
    device.issue_request<PABB_MSG_COMMAND_RESUME_GAME_BACK_OUT>(params);
}

void resume_game_front_of_den_nowatts(bool tolerate_update_menu){
    resume_game_front_of_den_nowatts(*global_connection, tolerate_update_menu);
}
void resume_game_front_of_den_nowatts(PABotBase& device, bool tolerate_update_menu){
    resume_game_back_out(device, tolerate_update_menu, 400);
}

void reset_game_from_home(bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    reset_game_from_home(*global_connection, tolerate_update_menu, user_slot, game_slot2);
}
void reset_game_from_home(PABotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    pabb_reset_game_from_home params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.user_slot = user_slot;
    params.game_slot2 = game_slot2;
    device.issue_request<PABB_MSG_COMMAND_RESET_GAME_FROM_HOME>(params);
}

void settings_to_enter_game(bool fast, uint16_t delay){
    settings_to_enter_game(*global_connection, fast, delay);
}
void settings_to_enter_game(PABotBase& device, bool fast, uint16_t delay){
    pabb_settings_to_enter_game params;
    params.fast = fast;
    params.delay = delay;
    device.issue_request<PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME>(params);
}
void settings_to_enter_game_den_lobby(bool tolerate_update_menu, bool fast){
    settings_to_enter_game_den_lobby(*global_connection, tolerate_update_menu, fast);
}
void settings_to_enter_game_den_lobby(PABotBase& device, bool tolerate_update_menu, bool fast){
    pabb_settings_to_enter_game_den_lobby params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY>(params);
}
void start_game_from_home(bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save){
    start_game_from_home(*global_connection, tolerate_update_menu, game_slot, user_slot, backup_save);
}
void start_game_from_home(PABotBase& device, bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save){
    pabb_start_game_from_home params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.game_slot = game_slot;
    params.user_slot = user_slot;
    params.backup_save = backup_save;
    device.issue_request<PABB_MSG_COMMAND_START_GAME_FROM_HOME>(params);
}
void close_game(void){
    close_game(*global_connection);
}
void close_game(PABotBase& device){
    pabb_close_game params;
    device.issue_request<PABB_MSG_COMMAND_CLOSE_GAME>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Date Spam
void home_to_date_time(bool fast){
    home_to_date_time(*global_connection, fast);
}
void home_to_date_time(PABotBase& device, bool fast){
    pabb_home_to_date_time params;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_HOME_TO_DATE_TIME>(params);
}

void roll_date_forward_1(bool fast){
    roll_date_forward_1(*global_connection, fast);
}
void roll_date_forward_1(PABotBase& device, bool fast){
    pabb_roll_date_forward_1 params;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1>(params);
}

void roll_date_backward_N(uint8_t skips, bool fast){
    roll_date_backward_N(*global_connection, skips, fast);
}
void roll_date_backward_N(PABotBase& device, uint8_t skips, bool fast){
    pabb_roll_date_backward_N params;
    params.skips = skips;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N>(params);
}

#define END_YEAR    60
void home_roll_date_enter_game_autorollback(uint16_t delay){
    home_roll_date_enter_game_autorollback(*global_connection, delay);
}
void home_roll_date_enter_game_autorollback(PABotBase& device, uint16_t delay){
    //  This version automatically handles the 2060 roll-back.

    static uint8_t year = END_YEAR;

    if (year >= END_YEAR){
        home_roll_date_enter_game(device, true, delay);
        year = 0;
    }else{
        home_roll_date_enter_game(device, false, delay);
    }
    year++;
}

void home_roll_date_enter_game(bool rollback_year, uint16_t delay){
    home_roll_date_enter_game(*global_connection, rollback_year, delay);
}
void home_roll_date_enter_game(PABotBase& device, bool rollback_year, uint16_t delay){
    pabb_home_roll_date_enter_game params;
    params.rollback_year = rollback_year;
    params.delay = delay;
    device.issue_request<PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME>(params);
}

void touch_date_from_home(void){
    touch_date_from_home(*global_connection);
}
void touch_date_from_home(PABotBase& device){
    pabb_touch_date_from_home params;
    device.issue_request<PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME>(params);
}

void rollback_hours_from_home(uint8_t hours){
    rollback_hours_from_home(*global_connection, hours);
}
void rollback_hours_from_home(PABotBase& device, uint8_t hours){
    pabb_rollback_hours_from_home params;
    params.hours = hours;
    device.issue_request<PABB_MSG_COMMAND_ROLLBACK_HOURS_FROM_HOME>(params);
}
