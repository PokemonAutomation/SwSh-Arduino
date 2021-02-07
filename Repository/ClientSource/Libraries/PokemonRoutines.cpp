/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include "Common/DeviceFramework/FrameworkSettings.h"
#include "Common/DeviceFramework/PushButtons.h"
#include "Common/Pokemon/PokemonSettings.h"
#include "Common/Pokemon/PokemonRoutines.h"
#include "ClientSource/Libraries/Compiler.h"
#include "ClientSource/Connection/BotBase.h"

using namespace PokemonAutomation;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Game Entry

void mash_A(uint16_t ticks){
    mash_A(*global_connection, ticks);
}
void mash_A(PokemonAutomation::BotBase& device, uint16_t ticks){
    pabb_mashA params;
    params.ticks = ticks;
    device.issue_request<PABB_MSG_COMMAND_MASH_A>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Game Entry

void resume_game_no_interact(bool tolerate_update_menu){
    resume_game_no_interact(*global_connection, tolerate_update_menu);
}
void resume_game_no_interact(BotBase& device, bool tolerate_update_menu){
    if (tolerate_update_menu){
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
        pbf_press_dpad(device, DPAD_DOWN, 10, 10);
        pbf_press_dpad(device, DPAD_UP, 10, 10);
        pbf_press_button(device, BUTTON_A, 10, HOME_TO_GAME_DELAY);
    }else{
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
    }
}

void resume_game_back_out(bool tolerate_update_menu, uint16_t mash_B_time){
    resume_game_back_out(*global_connection, tolerate_update_menu, mash_B_time);
}
void resume_game_back_out(BotBase& device, bool tolerate_update_menu, uint16_t mash_B_time){
    if (tolerate_update_menu){
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
        pbf_press_dpad(device, DPAD_DOWN, 10, 10);
        pbf_press_dpad(device, DPAD_UP, 10, 10);
        pbf_press_button(device, BUTTON_A, 10, HOME_TO_GAME_DELAY);
        pbf_mash_button(device, BUTTON_B, mash_B_time);
    }else{
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
    }
}

void resume_game_front_of_den_nowatts(bool tolerate_update_menu){
    resume_game_front_of_den_nowatts(*global_connection, tolerate_update_menu);
}
void resume_game_front_of_den_nowatts(BotBase& device, bool tolerate_update_menu){
    resume_game_back_out(device, tolerate_update_menu, 400);
}

void fast_reset_game(
    uint16_t start_game_mash, uint16_t start_game_wait,
    uint16_t enter_game_mash, uint16_t enter_game_wait
){
    fast_reset_game(
        *global_connection,
        start_game_mash, start_game_wait,
        enter_game_mash, enter_game_wait
    );
}
void fast_reset_game(
    BotBase& device,
    uint16_t start_game_mash, uint16_t start_game_wait,
    uint16_t enter_game_mash, uint16_t enter_game_wait
){
    pabb_fast_reset_game params;
    params.start_game_mash = start_game_mash;
    params.start_game_wait = start_game_wait;
    params.enter_game_mash = enter_game_mash;
    params.enter_game_wait = enter_game_wait;
    device.issue_request<PABB_MSG_COMMAND_FAST_RESET_GAME>(params);
}

void reset_game_from_home(bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    reset_game_from_home(*global_connection, tolerate_update_menu, user_slot, game_slot2);
}
void reset_game_from_home(BotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
#if 0
    pabb_reset_game_from_home params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.user_slot = user_slot;
    params.game_slot2 = game_slot2;
    device.issue_request<PABB_MSG_COMMAND_RESET_GAME_FROM_HOME>(params);
#else
    //  If "user_slot" is 0, start whatever the current user is.
    //  If "game_slot2" is true, start the game in the 2nd slot instead of the 1st slot.

    if (!START_GAME_REQUIRES_INTERNET &&
        !tolerate_update_menu &&
        user_slot == 0 && !game_slot2
    ){
        fast_reset_game(
            START_GAME_MASH, START_GAME_WAIT,
            ENTER_GAME_MASH, ENTER_GAME_WAIT
        );
        return;
    }

    close_game();

    start_game_from_home(
        tolerate_update_menu,
        game_slot2 ? 2 : 0,
        user_slot,
        false
    );
#endif
}

void settings_to_enter_game(bool fast){
    settings_to_enter_game(*global_connection, fast);
}
void settings_to_enter_game(BotBase& device, bool fast){
    if (fast){
        //  100 ticks for the first press isn't enough to finish the animation.
        //  But since the HOME button has delayed effect, we start pressing the 2nd
        //  press before the animation finishes.
        pbf_press_button(device, BUTTON_HOME, 10, 90);
        pbf_press_button(device, BUTTON_HOME, 10, 0);
    }else{
        pbf_press_button(device, BUTTON_HOME, 10, 190);
        pbf_press_button(device, BUTTON_HOME, 10, 0);
    }
}

void settings_to_enter_game_den_lobby(bool tolerate_update_menu, bool fast){
    settings_to_enter_game_den_lobby(*global_connection, tolerate_update_menu, fast);
}
void settings_to_enter_game_den_lobby(BotBase& device, bool tolerate_update_menu, bool fast){
    pabb_settings_to_enter_game_den_lobby params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY>(params);
}

void start_game_from_home(bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save){
    start_game_from_home(*global_connection, tolerate_update_menu, game_slot, user_slot, backup_save);
}
void start_game_from_home(BotBase& device, bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save){
    //  Start the game with the specified "game_slot" and "user_slot".
    //  If "game_slot" is zero, it uses whatever the cursor is on.
    //  If "user_slot" is zero, it uses whatever the cursor is on.

    if (game_slot != 0){
        pbf_press_button(BUTTON_HOME, 10, SETTINGS_TO_HOME_DELAY - 10);
        for (uint8_t c = 1; c < game_slot; c++){
            pbf_press_dpad(DPAD_RIGHT, 5, 5);
        }
    }

    if (tolerate_update_menu){
        //  If the update menu isn't there, these will get swallowed by the opening
        //  animation for the select user menu.
        pbf_press_button(BUTTON_A, 5, 35);  //  Choose game
        pbf_press_dpad(DPAD_UP, 5, 0);      //  Skip the update window.
    }

    if (!START_GAME_REQUIRES_INTERNET && user_slot == 0){
        //  Mash your way into the game.
        pbf_mash_button(BUTTON_A, START_GAME_MASH);
    }else{
        pbf_press_button(BUTTON_A, 5, 175);     //  Enter select user menu.
        if (user_slot != 0){
            //  Move to correct user.
            for (uint8_t c = 0; c < 8; c++){
                pbf_press_dpad(DPAD_LEFT, 7, 7);
            }
//            pbf_wait(50);
            for (uint8_t c = 1; c < user_slot; c++){
                pbf_press_dpad(DPAD_RIGHT, 7, 7);
            }
        }
        pbf_press_button(BUTTON_A, 5, 5);       //  Enter game

        //  Switch to mashing ZR instead of A to get into the game.
        //  Mash your way into the game.
        uint16_t duration = START_GAME_MASH;
        if (START_GAME_REQUIRES_INTERNET){
            //  Need to wait a bit longer for the internet check.
            duration += START_GAME_INTERNET_CHECK_DELAY;
        }
        pbf_mash_button(BUTTON_ZR, duration);
    }

    enter_game(backup_save, ENTER_GAME_MASH, ENTER_GAME_WAIT);
}

void enter_game(bool backup_save, uint16_t enter_game_mash, uint16_t enter_game_wait){
    enter_game(*global_connection, backup_save, enter_game_mash, enter_game_wait);
}
void enter_game(PokemonAutomation::BotBase& device, bool backup_save, uint16_t enter_game_mash, uint16_t enter_game_wait){
    pabb_enter_game params;
    params.backup_save = backup_save;
    params.enter_game_mash = enter_game_mash;
    params.enter_game_wait = enter_game_wait;
    device.issue_request<PABB_MSG_COMMAND_ENTER_GAME>(params);
}

void close_game(void){
    close_game(*global_connection);
}
void close_game(BotBase& device){
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
void home_to_date_time(BotBase& device, bool fast){
    pabb_home_to_date_time params;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_HOME_TO_DATE_TIME>(params);
}

void roll_date_forward_1(bool fast){
    roll_date_forward_1(*global_connection, fast);
}
void roll_date_forward_1(BotBase& device, bool fast){
    pabb_roll_date_forward_1 params;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1>(params);
}

void roll_date_backward_N(uint8_t skips, bool fast){
    roll_date_backward_N(*global_connection, skips, fast);
}
void roll_date_backward_N(BotBase& device, uint8_t skips, bool fast){
    pabb_roll_date_backward_N params;
    params.skips = skips;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N>(params);
}

void home_roll_date_enter_game_autorollback(uint8_t* year){
    home_roll_date_enter_game_autorollback(*global_connection, year);
}
void home_roll_date_enter_game_autorollback(BotBase& device, uint8_t* year){
    //  This version automatically handles the 2060 roll-back.
    if (*year >= MAX_YEAR){
        home_roll_date_enter_game(true);
        *year = 0;
    }else{
        home_roll_date_enter_game(false);
    }
    (*year)++;
}

void home_roll_date_enter_game(bool rollback_year){
    home_roll_date_enter_game(*global_connection, rollback_year);
}
void home_roll_date_enter_game(BotBase& device, bool rollback_year){
    pabb_home_roll_date_enter_game params;
    params.rollback_year = rollback_year;
    device.issue_request<PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME>(params);
}

void touch_date_from_home(uint16_t settings_to_home_delay){
    touch_date_from_home(*global_connection, settings_to_home_delay);
}
void touch_date_from_home(BotBase& device, uint16_t settings_to_home_delay){
    pabb_touch_date_from_home params;
    params.settings_to_home_delay = settings_to_home_delay;
    device.issue_request<PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME>(params);
}

void rollback_hours_from_home(uint8_t hours, uint16_t settings_to_home_delay){
    rollback_hours_from_home(*global_connection, hours, settings_to_home_delay);
}
void rollback_hours_from_home(BotBase& device, uint8_t hours, uint16_t settings_to_home_delay){
    pabb_rollback_hours_from_home params;
    params.hours = hours;
    params.settings_to_home_delay = settings_to_home_delay;
    device.issue_request<PABB_MSG_COMMAND_ROLLBACK_HOURS_FROM_HOME>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Mass Release

void release(void){
    release(*global_connection);
}
void release(BotBase& device){
    pabb_release params;
    device.issue_request<PABB_MSG_COMMAND_RELEASE>(params);
}
void release_boxes(uint8_t boxes, uint16_t box_scroll_delay, uint16_t box_change_delay){
    release_boxes(*global_connection, boxes, box_scroll_delay, box_change_delay);
}
void release_boxes(BotBase& device, uint8_t boxes, uint16_t box_scroll_delay, uint16_t box_change_delay){
    pabb_release_boxes params;
    params.boxes = boxes;
    params.box_scroll_delay = box_scroll_delay;
    params.box_change_delay = box_change_delay;
    device.issue_request<PABB_MSG_COMMAND_RELEASE_BOXES>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Fast Code Entry

void enter_8digits_str(const char digits[8]){
    enter_8digits((const uint8_t*)digits);
}
void enter_8digits_str(PokemonAutomation::BotBase& device, const char digits[8]){
    enter_8digits(device, (const uint8_t*)digits);
}
void enter_8digits(const uint8_t digits[8]){
    enter_8digits(*global_connection, digits);
}
uint8_t convert_digit(uint8_t digit){
    if (digit >= '0'){
        digit -= '0';
    }
    if (digit > 9){
        digit = 0;
    }
    return digit;
}
void enter_8digits(PokemonAutomation::BotBase& device, const uint8_t digits[8]){
    pabb_enter_8digits params;
    params.digit01 = convert_digit(digits[0]) | (convert_digit(digits[1]) << 4);
    params.digit23 = convert_digit(digits[2]) | (convert_digit(digits[3]) << 4);
    params.digit45 = convert_digit(digits[4]) | (convert_digit(digits[5]) << 4);
    params.digit67 = convert_digit(digits[6]) | (convert_digit(digits[7]) << 4);
    device.issue_request<PABB_MSG_COMMAND_ENTER_8DIGITS>(params);

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Auto-Hosting

void connect_to_internet(uint16_t open_ycomm_delay, uint16_t connect_to_internet_delay){
    connect_to_internet(*global_connection, open_ycomm_delay, connect_to_internet_delay);
}
void connect_to_internet(
    PokemonAutomation::BotBase& device,
    uint16_t open_ycomm_delay,
    uint16_t connect_to_internet_delay
){
    pabb_connect_to_internet params;
    params.open_ycomm_delay = open_ycomm_delay;
    params.connect_to_internet_delay = connect_to_internet_delay;
    device.issue_request<PABB_MSG_COMMAND_CONNECT_TO_INTERNET>(params);
}
void accept_FRs_while_waiting(
    uint8_t slot, uint16_t wait_time,
    uint16_t game_to_home_delay_safe,
    uint16_t auto_fr_duration,
    bool tolerate_system_update_window_slow
){
    accept_FRs_while_waiting(
        *global_connection,
        slot, wait_time,
        game_to_home_delay_safe,
        auto_fr_duration,
        tolerate_system_update_window_slow
    );
}
void accept_FRs_while_waiting(
    PokemonAutomation::BotBase& device,
    uint8_t slot, uint16_t wait_time,
    uint16_t game_to_home_delay_safe,
    uint16_t auto_fr_duration,
    bool tolerate_system_update_window_slow
){
    pabb_accept_FRs_while_waiting params;
    params.slot = slot;
    params.wait_time = wait_time;
    params.game_to_home_delay_safe = game_to_home_delay_safe;
    params.auto_fr_duration = auto_fr_duration;
    params.tolerate_system_update_window_slow = tolerate_system_update_window_slow;
    device.issue_request<PABB_MSG_COMMAND_ACCEPT_FRS_WHILE_WAITING>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Misc. (PABB_PABOTBASE_LEVEL >= 31)

void IoA_backout(uint16_t pokemon_to_menu_delay){
    IoA_backout(*global_connection, pokemon_to_menu_delay);
}
void IoA_backout(PokemonAutomation::BotBase& device, uint16_t pokemon_to_menu_delay){
    pabb_IoA_backout params;
    params.pokemon_to_menu_delay = pokemon_to_menu_delay;
    device.issue_request<PABB_MSG_COMMAND_IOA_BACKOUT>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Day Skippers (PABB_PABOTBASE_LEVEL >= 31)

void skipper_init_view(void){
    skipper_init_view(*global_connection);
}
void skipper_init_view(PokemonAutomation::BotBase& device){
    pabb_skipper_init_view params;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_INIT_VIEW>(params);
}
void skipper_auto_recovery(void){
    skipper_auto_recovery(*global_connection);
}
void skipper_auto_recovery(PokemonAutomation::BotBase& device){
    pabb_skipper_auto_recovery params;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_AUTO_RECOVERY>(params);
}
void skipper_rollback_year_full(bool date_us){
    skipper_rollback_year_full(*global_connection, date_us);
}
void skipper_rollback_year_full(PokemonAutomation::BotBase& device, bool date_us){
    pabb_skipper_rollback_year_full params;
    params.date_us = date_us;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_ROLLBACK_YEAR_FULL>(params);
}
void skipper_rollback_year_sync(void){
    skipper_rollback_year_sync(*global_connection);
}
void skipper_rollback_year_sync(PokemonAutomation::BotBase& device){
    pabb_skipper_rollback_year_sync params;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_ROLLBACK_YEAR_SYNC>(params);
}
void skipper_increment_day(bool date_us){
    skipper_increment_day(*global_connection, date_us);
}
void skipper_increment_day(PokemonAutomation::BotBase& device, bool date_us){
    pabb_skipper_increment_day params;
    params.date_us = date_us;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_INCREMENT_DAY>(params);
}
void skipper_increment_month(uint8_t days){
    skipper_increment_month(*global_connection, days);
}
void skipper_increment_month(PokemonAutomation::BotBase& device, uint8_t days){
    pabb_skipper_increment_month params;
    params.days = days;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_INCREMENT_MONTH>(params);
}
void skipper_increment_all(void){
    skipper_increment_all(*global_connection);
}
void skipper_increment_all(PokemonAutomation::BotBase& device){
    pabb_skipper_increment_all params;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_INCREMENT_ALL>(params);
}
void skipper_increment_all_rollback(void){
    skipper_increment_all_rollback(*global_connection);
}
void skipper_increment_all_rollback(PokemonAutomation::BotBase& device){
    pabb_skipper_increment_all_rollback params;
    device.issue_request<PABB_MSG_COMMAND_SKIPPER_INCREMENT_ALL_ROLLBACK>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Eggs (PABB_PABOTBASE_LEVEL >= 31)

void eggfetcher_loop(void){
    eggfetcher_loop(*global_connection);
}
void eggfetcher_loop(PokemonAutomation::BotBase& device){
    pabb_eggfetcher_loop params;
    device.issue_request<PABB_MSG_COMMAND_EGG_FETCHER_LOOP>(params);
}
void move_while_mashing_B(uint16_t duration){
    move_while_mashing_B(*global_connection, duration);
}
void move_while_mashing_B(PokemonAutomation::BotBase& device, uint16_t duration){
    pabb_move_while_mashing_B params;
    params.duration = duration;
    device.issue_request<PABB_MSG_COMMAND_MOVE_WHILE_MASHING_B>(params);
}
void spin_and_mash_A(uint16_t duration){
    spin_and_mash_A(*global_connection, duration);
}
void spin_and_mash_A(PokemonAutomation::BotBase& device, uint16_t duration){
    pabb_spin_and_mash_A params;
    params.duration = duration;
    device.issue_request<PABB_MSG_COMMAND_SPIN_AND_MASH_A>(params);
}
void travel_to_spin_location(void){
    travel_to_spin_location(*global_connection);
}
void travel_to_spin_location(PokemonAutomation::BotBase& device){
    pabb_travel_to_spin_location params;
    device.issue_request<PABB_MSG_COMMAND_TRAVEL_TO_SPIN_LOCATION>(params);
}
void travel_back_to_lady(void){
    travel_back_to_lady(*global_connection);
}
void travel_back_to_lady(PokemonAutomation::BotBase& device){
    pabb_travel_back_to_lady params;
    device.issue_request<PABB_MSG_COMMAND_TRAVEL_BACK_TO_LADY>(params);
}


