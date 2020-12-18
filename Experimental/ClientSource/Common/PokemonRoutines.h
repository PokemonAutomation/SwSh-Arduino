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
class PABotBase;
void resume_game_no_interact            (PABotBase& device, bool tolerate_update_menu);
void resume_game_back_out               (PABotBase& device, bool tolerate_update_menu, uint16_t mash_B_time);
void resume_game_front_of_den_nowatts   (PABotBase& device, bool tolerate_update_menu);
void reset_game_from_home               (PABotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2);
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


#define PABB_MSG_COMMAND_RESUME_GAME_NO_INTERACT            0x40
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
} PABB_PACK pabb_resume_game_no_interact;

#define PABB_MSG_COMMAND_RESUME_GAME_BACK_OUT               0x41
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint16_t mash_B_time;
} PABB_PACK pabb_resume_game_back_out;

#define PABB_MSG_COMMAND_RESUME_GAME_FRONT_OF_DEN_NOWATTS   0x42
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
} PABB_PACK pabb_resume_game_front_of_den_nowatts;

#define PABB_MSG_COMMAND_RESET_GAME_FROM_HOME               0x43
typedef struct{
    uint8_t seqnum;
    bool tolerate_update_menu;
    uint8_t user_slot;
    bool game_slot2;
} PABB_PACK pabb_reset_game_from_home;


#if _WIN32
#pragma pack(pop)
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
