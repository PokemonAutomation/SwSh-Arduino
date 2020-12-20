/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_PokemonRoutines_H
#define PokemonAutomation_PokemonRoutines_H

#ifdef __AVR__
#include "Framework/Master.h"
#endif
#include "ControllerDefs.h"

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
//  "delay" specifies how long to wait after the final press to re-enter the game.
uint16_t settings_to_enter_game(bool fast, uint16_t delay);

//  From anywhere in the Switch settings except the home menu, return to the game.
//  Return to the game where you are inside an open den lobby with the cursor over
//  "Switch Pokemon".
uint16_t settings_to_enter_game_den_lobby(bool tolerate_update_menu, bool fast);

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
//  Date Spam

//  From the Switch Home, navigate all the way to the date change button.
//  If (fast = true), it will run slightly faster, but has a higher chance of
//  not making all way in. Do this only if the program is able to self-recover.
void home_to_date_time(bool fast);

//  Call this immediately after calling "home_to_date_time()".
//  This function will roll the 1st and 3rd slots forward by one.
void roll_date_forward_1(bool fast);

//  Call this immediately after calling "home_to_date_time()".
//  This function will roll the 1st and 3rd slots backwards by N.
void roll_date_backward_N(uint8_t skips, bool fast);

//  From inside the game:
//      1.  Go to Switch Home.
//      2.  Roll the date forward.
//      3.  Return to the game.
//      4.  Wait "delay" ticks. (recommend at least 100 ticks)
//
//  The first time you call this function, it will roll the year back to 2000.
//  Then every 60 calls, it will roll it back to 2000 again. It automatically
//  keeps track of this count.
//
void home_roll_date_enter_game_autorollback(uint16_t delay);

//  From inside the game:
//      1.  Go to Switch Home.
//      2.  Roll the date forward.
//      3.  Return to the game.
//      4.  Wait "delay" ticks. (recommend at least 100 ticks)
//
//  This function does not automatically roll back the year to 2000. You tell it
//  whether to do roll back with the "rollback_year" parameter.
//
void home_roll_date_enter_game(bool rollback_year, uint16_t delay);

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
uint16_t settings_to_enter_game             (PokemonAutomation::PABotBase& device, bool fast, uint16_t delay);
uint16_t settings_to_enter_game_den_lobby   (PokemonAutomation::PABotBase& device, bool tolerate_update_menu, bool fast);
void start_game_from_home                   (PokemonAutomation::PABotBase& device, bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save);
void close_game                             (PokemonAutomation::PABotBase& device);
void home_to_date_time                      (PokemonAutomation::PABotBase& device, bool fast);
void roll_date_forward_1                    (PokemonAutomation::PABotBase& device, bool fast);
void roll_date_backward_N                   (PokemonAutomation::PABotBase& device, uint8_t skips, bool fast);
void home_roll_date_enter_game              (PokemonAutomation::PABotBase& device, bool rollback_year, uint16_t delay);
void home_roll_date_enter_game_autorollback (PokemonAutomation::PABotBase& device, uint16_t delay);
void touch_date_from_home                   (PokemonAutomation::PABotBase& device);
void rollback_hours_from_home               (PokemonAutomation::PABotBase& device, uint8_t hours);
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


#define PABB_MSG_COMMAND_RESUME_GAME_NO_INTERACT                0x40
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
} PABB_PACK pabb_resume_game_no_interact;

#define PABB_MSG_COMMAND_RESUME_GAME_BACK_OUT                   0x41
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint16_t mash_B_time;
} PABB_PACK pabb_resume_game_back_out;

#define PABB_MSG_COMMAND_RESUME_GAME_FRONT_OF_DEN_NOWATTS       0x42
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
} PABB_PACK pabb_resume_game_front_of_den_nowatts;

#define PABB_MSG_COMMAND_RESET_GAME_FROM_HOME                   0x43
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint8_t user_slot;
    bool game_slot2;
} PABB_PACK pabb_reset_game_from_home;

#define PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME                 0x44
typedef struct{
    uint8_t seqnum;
    bool fast;
    uint16_t delay;
} PABB_PACK pabb_settings_to_enter_game;

#define PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY       0x45
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    bool fast;
} PABB_PACK pabb_settings_to_enter_game_den_lobby;

#define PABB_MSG_COMMAND_START_GAME_FROM_HOME                   0x46
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint8_t game_slot;
    uint8_t user_slot;
    bool backup_save;
} PABB_PACK pabb_start_game_from_home;

#define PABB_MSG_COMMAND_CLOSE_GAME                             0x47
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_close_game;

#define PABB_MSG_COMMAND_HOME_TO_DATE_TIME                      0x50
typedef struct{
    uint8_t seqnum;
    bool fast;
} PABB_PACK pabb_home_to_date_time;

#define PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1                    0x51
typedef struct{
    uint8_t seqnum;
    bool fast;
} PABB_PACK pabb_roll_date_forward_1;

#define PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N                   0x52
typedef struct{
    uint8_t seqnum;
    uint8_t skips;
    bool fast;
} PABB_PACK pabb_roll_date_backward_N;

#define PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME              0x53
typedef struct{
    uint8_t seqnum;
    bool rollback_year;
    uint16_t delay;
} PABB_PACK pabb_home_roll_date_enter_game;

#define PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME_AUTOROLLBACK 0x54
typedef struct{
    uint8_t seqnum;
    uint16_t delay;
} PABB_PACK pabb_home_roll_date_enter_game_autorollback;

#define PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME                   0x55
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_touch_date_from_home;

#define PABB_MSG_COMMAND_ROLLBACK_HOURS_FROM_HOME               0x56
typedef struct{
    uint8_t seqnum;
    uint8_t hours;
} PABB_PACK pabb_rollback_hours_from_home;


#if _WIN32
#pragma pack(pop)
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
