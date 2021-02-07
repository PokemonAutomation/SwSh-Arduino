/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_PokemonRoutines_H
#define PokemonAutomation_PokemonRoutines_H

#ifdef __AVR__
#include "DeviceSource/DeviceFramework/Master.h"
#endif
#include "Common/DeviceFramework/SwitchControllerDefs.h"

#ifdef __AVR_ATmega16U2__
#define PABB_PABOTBASE_LEVEL    12
#elif __AVR_ATmega32U4__
#define PABB_PABOTBASE_LEVEL    31
#elif __AVR_AT90USB1286__
#define PABB_PABOTBASE_LEVEL    127
#elif __cplusplus
#define PABB_PABOTBASE_LEVEL    1000
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Shared API
#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Misc.

void mash_A(uint16_t ticks);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Game Entry

//  From the Switch home menu, resume the game.
//  Nothing in front of you should be interactable.
void resume_game_no_interact(bool tolerate_update_menu);

//  From the Switch home menu, resume the game.
//  If something in front of you is interactable, you should be able to back out
//  by mashing B.
void resume_game_back_out(bool tolerate_update_menu, uint16_t mash_B_time);

//  From the Switch home menu, resume the game.
//  You may be standing in front of a den.
void resume_game_front_of_den_nowatts(bool tolerate_update_menu);

//  With the cursor over the game you wish to reset, close and reopen the game
//  from the same user. There must be no system update window and starting the
//  game must not require checking the internet.
void fast_reset_game(
    uint16_t start_game_mash, uint16_t start_game_wait,
    uint16_t enter_game_mash, uint16_t enter_game_wait
);

//  From the Switch home menu, close the game and open another game.
//      If "user_slot" is 0, start whatever the current user is.
//      If "game_slot2" is true, start the game in the 2nd slot instead of the 1st slot.
void reset_game_from_home(bool tolerate_update_menu, uint8_t user_slot, bool game_slot2);

//  From anywhere in the Switch settings except the home menu, return to the game.
//  This operation is intended to be fast.
//  If (fast = true), it will run faster, but with a small chance of not making it into the game.
//
//  This function does not wait after the final press. Recommend waiting 100 ticks
//  before you are safely in the game.
void settings_to_enter_game(bool fast);

//  From anywhere in the Switch settings except the home menu, return to the game.
//  Return to the game where you are inside an open den lobby with the cursor over
//  "Switch Pokemon".
void settings_to_enter_game_den_lobby(bool tolerate_update_menu, bool fast);

//  From the Switch home with the cursor over the 1st game and the game closed,
//  start the specified game. When the function returns, you should be in the
//  game and ready to play. (not the loading menu)
void start_game_from_home(
    bool tolerate_update_menu,
    uint8_t game_slot,
    uint8_t user_slot,
    bool backup_save
);

//  Enter the game when you're sitting in the game intro.
void enter_game(bool backup_save, uint16_t enter_game_mash, uint16_t enter_game_wait);

//  With the cursor over the game you wish to close, close it in a reliable manner.
void close_game(void);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Optimized Date Spam

//  From the Switch Home (cursor over 1st game), navigate all the way to the
//  date change button.
//  If (fast = true), it will run slightly faster, but has a higher chance of
//  not making all way in. Do this only if the program is able to self-recover.
void home_to_date_time(bool fast);

//  Call this immediately after calling "home_to_date_time()".
//  This function will roll the 1st and 3rd slots forward by one.
void roll_date_forward_1(bool fast);

//  Call this immediately after calling "home_to_date_time()".
//  This function will roll the 1st and 3rd slots backwards by N.
void roll_date_backward_N(uint8_t skips, bool fast);

//  From the Switch Home (cursor over 1st game), roll the date forward and
//  re-enter the game.
//
//  This function does not wait after the final press. Recommend waiting 100 ticks
//  before you are safely in the game.
//
//  The first time you call this function, it will roll the year back to 2000.
//  Then every 60 calls, it will roll it back to 2000 again. It automatically
//  keeps track of this count.
//
#define MAX_YEAR    60
void home_roll_date_enter_game_autorollback(uint8_t* year);

//  From the Switch Home (cursor over 1st game), roll the date forward and
//  re-enter the game.
//
//  This function does not wait after the final press. Recommend waiting 100 ticks
//  before you are safely in the game.
//
//  This function does not automatically roll back the year to 2000. You tell it
//  whether to do roll back with the "rollback_year" parameter.
//
void home_roll_date_enter_game(bool rollback_year);

//  Touch the date without changing it. This prevents unintentional rollovers.
//  Start this function in the Switch home with the icon over the first game.
//  When the function finishes, it will be back in the same position.
void touch_date_from_home(uint16_t settings_to_home_delay);

//  Roll back by this many hours.
//  Start this function in the Switch home with the icon over the first game.
//  When the function finishes, it will be back in the same position.
void rollback_hours_from_home(uint8_t hours, uint16_t settings_to_home_delay);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Mass Release (PABB_PABOTBASE_LEVEL >= 31)

//  With the red cursor over a Pokemon, release it.
void release(void);

//  With the red cursor over the 1st Pokemon in the box, release this many boxes.
void release_boxes(uint8_t boxes, uint16_t box_scroll_delay, uint16_t box_change_delay);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Fast Code Entry (PABB_PABOTBASE_LEVEL >= 12)

//  With the cursor over the '1' digit, enter 8 digits. Each digit can be either
//  a raw integer (0-9), or ascii '0' - '9'. If the digit is invalid, it will be
//  get converted to 0.
void enter_8digits_str  (const char digits[8]);
void enter_8digits      (const uint8_t digits[8]);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Auto-Hosting (PABB_PABOTBASE_LEVEL >= 12)

void connect_to_internet(uint16_t open_ycomm_delay, uint16_t connect_to_internet_delay);
void accept_FRs_while_waiting(
    uint8_t slot, uint16_t wait_time,
    uint16_t game_to_home_delay_safe,
    uint16_t auto_fr_duration,
    bool tolerate_system_update_window_slow
);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Eggs (PABB_PABOTBASE_LEVEL >= 31)

void eggfetcher_loop        (void);
void move_while_mashing_B   (uint16_t duration);
void spin_and_mash_A        (uint16_t duration);
void travel_to_spin_location(void);
void travel_back_to_lady    (void);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Client Side Extensions
#ifdef __cplusplus
namespace PokemonAutomation{
    class BotBase;
}
void mash_A                                 (PokemonAutomation::BotBase& device, uint16_t ticks);
void resume_game_no_interact                (PokemonAutomation::BotBase& device, bool tolerate_update_menu);
void resume_game_back_out                   (PokemonAutomation::BotBase& device, bool tolerate_update_menu, uint16_t mash_B_time);
void resume_game_front_of_den_nowatts       (PokemonAutomation::BotBase& device, bool tolerate_update_menu);
void fast_reset_game(
    PokemonAutomation::BotBase& device,
    uint16_t start_game_mash, uint16_t start_game_wait,
    uint16_t enter_game_mash, uint16_t enter_game_wait
);
void reset_game_from_home                   (PokemonAutomation::BotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2);
void settings_to_enter_game                 (PokemonAutomation::BotBase& device, bool fast);
void settings_to_enter_game_den_lobby       (PokemonAutomation::BotBase& device, bool tolerate_update_menu, bool fast);
void start_game_from_home                   (PokemonAutomation::BotBase& device, bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save);
void enter_game                             (PokemonAutomation::BotBase& device, bool backup_save, uint16_t enter_game_mash, uint16_t enter_game_wait);
void close_game                             (PokemonAutomation::BotBase& device);
void home_to_date_time                      (PokemonAutomation::BotBase& device, bool fast);
void roll_date_forward_1                    (PokemonAutomation::BotBase& device, bool fast);
void roll_date_backward_N                   (PokemonAutomation::BotBase& device, uint8_t skips, bool fast);
void home_roll_date_enter_game              (PokemonAutomation::BotBase& device, bool rollback_year);
void home_roll_date_enter_game_autorollback (PokemonAutomation::BotBase& device, uint8_t* year);
void touch_date_from_home                   (PokemonAutomation::BotBase& device, uint16_t settings_to_home_delay);
void rollback_hours_from_home               (PokemonAutomation::BotBase& device, uint8_t hours, uint16_t settings_to_home_delay);
void release                                (PokemonAutomation::BotBase& device);
void release_boxes                          (PokemonAutomation::BotBase& device, uint8_t boxes, uint16_t box_scroll_delay, uint16_t box_change_delay);
void enter_8digits_str                      (PokemonAutomation::BotBase& device, const char digits[8]);
void enter_8digits                          (PokemonAutomation::BotBase& device, const uint8_t digits[8]);
void connect_to_internet                    (PokemonAutomation::BotBase& device, uint16_t open_ycomm_delay, uint16_t connect_to_internet_delay);
void accept_FRs_while_waiting(
    PokemonAutomation::BotBase& device,
    uint8_t slot, uint16_t wait_time,
    uint16_t game_to_home_delay_safe,
    uint16_t auto_fr_duration,
    bool tolerate_system_update_window_slow
);
void IoA_backout                            (uint16_t pokemon_to_menu_delay);
void IoA_backout                            (PokemonAutomation::BotBase& device, uint16_t pokemon_to_menu_delay);
void skipper_init_view                      (void);
void skipper_auto_recovery                  (void);
void skipper_rollback_year_full             (bool date_us);
void skipper_rollback_year_sync             (void);
void skipper_increment_day                  (bool date_us);
void skipper_increment_month                (uint8_t days);
void skipper_increment_all                  (void);
void skipper_increment_all_rollback         (void);
void skipper_init_view                      (PokemonAutomation::BotBase& device);
void skipper_auto_recovery                  (PokemonAutomation::BotBase& device);
void skipper_rollback_year_full             (PokemonAutomation::BotBase& device, bool date_us);
void skipper_rollback_year_sync             (PokemonAutomation::BotBase& device);
void skipper_increment_day                  (PokemonAutomation::BotBase& device, bool date_us);
void skipper_increment_month                (PokemonAutomation::BotBase& device, uint8_t days);
void skipper_increment_all                  (PokemonAutomation::BotBase& device);
void skipper_increment_all_rollback         (PokemonAutomation::BotBase& device);
void eggfetcher_loop                        (PokemonAutomation::BotBase& device);
void move_while_mashing_B                   (PokemonAutomation::BotBase& device, uint16_t duration);
void spin_and_mash_A                        (PokemonAutomation::BotBase& device, uint16_t duration);
void travel_to_spin_location                (PokemonAutomation::BotBase& device);
void travel_back_to_lady                    (PokemonAutomation::BotBase& device);

#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Message Protocols
#if _WIN32
#pragma pack(push, 1)
#define PABB_PACK
#else
#define PABB_PACK   __attribute__((packed))
#endif
////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_MASH_A                                 0xa0
typedef struct{
    uint8_t seqnum;
    uint16_t ticks;
} PABB_PACK pabb_mashA;

#define PABB_MSG_COMMAND_FAST_RESET_GAME                        0xa1
typedef struct{
    uint8_t seqnum;
    uint16_t start_game_mash;
    uint16_t start_game_wait;
    uint16_t enter_game_mash;
    uint16_t enter_game_wait;
} PABB_PACK pabb_fast_reset_game;

#define PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY       0xa2
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    bool fast;
} PABB_PACK pabb_settings_to_enter_game_den_lobby;

#define PABB_MSG_COMMAND_ENTER_GAME                             0xa3
typedef struct{
    uint8_t seqnum;
    bool backup_save;
    uint16_t enter_game_mash;
    uint16_t enter_game_wait;
} PABB_PACK pabb_enter_game;

#define PABB_MSG_COMMAND_CLOSE_GAME                             0xa4
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_close_game;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_HOME_TO_DATE_TIME                      0xa5
typedef struct{
    uint8_t seqnum;
    bool fast;
} PABB_PACK pabb_home_to_date_time;

#define PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1                    0xa6
typedef struct{
    uint8_t seqnum;
    bool fast;
} PABB_PACK pabb_roll_date_forward_1;

#define PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N                   0xa7
typedef struct{
    uint8_t seqnum;
    uint8_t skips;
    bool fast;
} PABB_PACK pabb_roll_date_backward_N;

#define PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME              0xa8
typedef struct{
    uint8_t seqnum;
    bool rollback_year;
} PABB_PACK pabb_home_roll_date_enter_game;

#define PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME                   0xa9
typedef struct{
    uint8_t seqnum;
    uint16_t settings_to_home_delay;
} PABB_PACK pabb_touch_date_from_home;

#define PABB_MSG_COMMAND_ROLLBACK_HOURS_FROM_HOME               0xaa
typedef struct{
    uint8_t seqnum;
    uint8_t hours;
    uint16_t settings_to_home_delay;
} PABB_PACK pabb_rollback_hours_from_home;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_RELEASE                                0xab
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_release;

#define PABB_MSG_COMMAND_RELEASE_BOXES                          0xac
typedef struct{
    uint8_t seqnum;
    uint8_t boxes;
    uint16_t box_scroll_delay;
    uint16_t box_change_delay;
} PABB_PACK pabb_release_boxes;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_ENTER_8DIGITS                          0xad
typedef struct{
    uint8_t seqnum;
    uint8_t digit01;
    uint8_t digit23;
    uint8_t digit45;
    uint8_t digit67;
} PABB_PACK pabb_enter_8digits;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_CONNECT_TO_INTERNET                    0xae
typedef struct{
    uint8_t seqnum;
    uint16_t open_ycomm_delay;
    uint16_t connect_to_internet_delay;
} PABB_PACK pabb_connect_to_internet;

#define PABB_MSG_COMMAND_ACCEPT_FRS_WHILE_WAITING               0xaf
typedef struct{
    uint8_t seqnum;
    uint8_t slot;
    uint16_t wait_time;
    uint16_t game_to_home_delay_safe;
    uint16_t auto_fr_duration;
    bool tolerate_system_update_window_slow;
} PABB_PACK pabb_accept_FRs_while_waiting;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_IOA_BACKOUT                            0xb0
typedef struct{
    uint8_t seqnum;
    uint16_t pokemon_to_menu_delay;
} PABB_PACK pabb_IoA_backout;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_SKIPPER_INIT_VIEW                      0xb1
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_skipper_init_view;

#define PABB_MSG_COMMAND_SKIPPER_AUTO_RECOVERY                  0xb2
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_skipper_auto_recovery;

#define PABB_MSG_COMMAND_SKIPPER_ROLLBACK_YEAR_FULL             0xb3
typedef struct{
    uint8_t seqnum;
    bool date_us;
} PABB_PACK pabb_skipper_rollback_year_full;

#define PABB_MSG_COMMAND_SKIPPER_ROLLBACK_YEAR_SYNC             0xb4
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_skipper_rollback_year_sync;

#define PABB_MSG_COMMAND_SKIPPER_INCREMENT_DAY                  0xb5
typedef struct{
    uint8_t seqnum;
    bool date_us;
} PABB_PACK pabb_skipper_increment_day;

#define PABB_MSG_COMMAND_SKIPPER_INCREMENT_MONTH                0xb6
typedef struct{
    uint8_t seqnum;
    uint8_t days;
} PABB_PACK pabb_skipper_increment_month;

#define PABB_MSG_COMMAND_SKIPPER_INCREMENT_ALL                  0xb7
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_skipper_increment_all;

#define PABB_MSG_COMMAND_SKIPPER_INCREMENT_ALL_ROLLBACK         0xb8
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_skipper_increment_all_rollback;

////////////////////////////////////////////////////////////////////////////////

#define PABB_MSG_COMMAND_EGG_FETCHER_LOOP                       0xb9
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_eggfetcher_loop;

#define PABB_MSG_COMMAND_MOVE_WHILE_MASHING_B                   0xba
typedef struct{
    uint8_t seqnum;
    uint16_t duration;
} PABB_PACK pabb_move_while_mashing_B;

#define PABB_MSG_COMMAND_SPIN_AND_MASH_A                        0xbb
typedef struct{
    uint8_t seqnum;
    uint16_t duration;
} PABB_PACK pabb_spin_and_mash_A;

#define PABB_MSG_COMMAND_TRAVEL_TO_SPIN_LOCATION                0xbc
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_travel_to_spin_location;

#define PABB_MSG_COMMAND_TRAVEL_BACK_TO_LADY                    0xbd
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_travel_back_to_lady;

////////////////////////////////////////////////////////////////////////////////
#if _WIN32
#pragma pack(pop)
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
