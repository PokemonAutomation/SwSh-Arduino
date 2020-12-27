/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_PokemonRoutines_H
#define PokemonAutomation_PokemonRoutines_H

#ifdef __AVR__
#include "DeviceFramework/Master.h"
#endif
#include "CommonFramework/ControllerDefs.h"

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
void home_roll_date_enter_game_autorollback(void);

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
void touch_date_from_home(void);

//  Roll back by this many hours.
//  Start this function in the Switch home with the icon over the first game.
//  When the function finishes, it will be back in the same position.
void rollback_hours_from_home(uint8_t hours);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Fast Code Entry

//  With the cursor over the '1' digit, enter 8 digits. Each digit can be either
//  a raw integer (0-9), or ascii '0' - '9'. If the digit is invalid, it will be
//  get converted to 0.
void enter_8digits_str  (const char digits[8]);
void enter_8digits      (const uint8_t digits[8]);

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
#ifndef __AVR__
namespace PokemonAutomation{
    class PABotBase;
}
void resume_game_no_interact                (PokemonAutomation::PABotBase& device, bool tolerate_update_menu);
void resume_game_back_out                   (PokemonAutomation::PABotBase& device, bool tolerate_update_menu, uint16_t mash_B_time);
void resume_game_front_of_den_nowatts       (PokemonAutomation::PABotBase& device, bool tolerate_update_menu);
void reset_game_from_home                   (PokemonAutomation::PABotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2);
void settings_to_enter_game                 (PokemonAutomation::PABotBase& device, bool fast);
void settings_to_enter_game_den_lobby       (PokemonAutomation::PABotBase& device, bool tolerate_update_menu, bool fast);
void start_game_from_home                   (PokemonAutomation::PABotBase& device, bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save);
void close_game                             (PokemonAutomation::PABotBase& device);
void home_to_date_time                      (PokemonAutomation::PABotBase& device, bool fast);
void roll_date_forward_1                    (PokemonAutomation::PABotBase& device, bool fast);
void roll_date_backward_N                   (PokemonAutomation::PABotBase& device, uint8_t skips, bool fast);
void home_roll_date_enter_game              (PokemonAutomation::PABotBase& device, bool rollback_year);
void home_roll_date_enter_game_autorollback (PokemonAutomation::PABotBase& device);
void touch_date_from_home                   (PokemonAutomation::PABotBase& device);
void rollback_hours_from_home               (PokemonAutomation::PABotBase& device, uint8_t hours);
void enter_8digits_str                      (PokemonAutomation::PABotBase& device, const char digits[8]);
void enter_8digits                          (PokemonAutomation::PABotBase& device, const uint8_t digits[8]);

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


#define PABB_MSG_COMMAND_RESET_GAME_FROM_HOME                   0xa0
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint8_t user_slot;
    bool game_slot2;
} PABB_PACK pabb_reset_game_from_home;

#define PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY       0xa1
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    bool fast;
} PABB_PACK pabb_settings_to_enter_game_den_lobby;

#define PABB_MSG_COMMAND_START_GAME_FROM_HOME                   0xa2
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint8_t game_slot;
    uint8_t user_slot;
    bool backup_save;
} PABB_PACK pabb_start_game_from_home;

#define PABB_MSG_COMMAND_CLOSE_GAME                             0xa3
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_close_game;

#define PABB_MSG_COMMAND_HOME_TO_DATE_TIME                      0xa4
typedef struct{
    uint8_t seqnum;
    bool fast;
} PABB_PACK pabb_home_to_date_time;

#define PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1                    0xa5
typedef struct{
    uint8_t seqnum;
    bool fast;
} PABB_PACK pabb_roll_date_forward_1;

#define PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N                   0xa6
typedef struct{
    uint8_t seqnum;
    uint8_t skips;
    bool fast;
} PABB_PACK pabb_roll_date_backward_N;

#define PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME              0xa7
typedef struct{
    uint8_t seqnum;
    bool rollback_year;
} PABB_PACK pabb_home_roll_date_enter_game;

#define PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME                   0xa8
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_touch_date_from_home;

#define PABB_MSG_COMMAND_ROLLBACK_HOURS_FROM_HOME               0xa9
typedef struct{
    uint8_t seqnum;
    uint8_t hours;
} PABB_PACK pabb_rollback_hours_from_home;

#define PABB_MSG_COMMAND_ENTER_8DIGITS                          0xaa
typedef struct{
    uint8_t seqnum;
    uint8_t digit01;
    uint8_t digit23;
    uint8_t digit45;
    uint8_t digit67;
} PABB_PACK pabb_enter_8digits;


#if _WIN32
#pragma pack(pop)
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
