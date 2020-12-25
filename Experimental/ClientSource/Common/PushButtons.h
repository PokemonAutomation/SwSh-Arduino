/*  Pokemon Automation Push Button Framework
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *      This is (will be) the public API. Try to use only these functions.
 * 
 */

#ifndef PokemonAutomation_PushButtons_H
#define PokemonAutomation_PushButtons_H

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
//  System Functions

//  Call this at the start of every program.
void initialize_framework(uint8_t program_id);

//  Turn on/off the LEDs.
void set_leds(bool on);

//  A global clock. Returns the # of ticks that have elapsed since the start of
//  the program.
uint32_t system_clock(void);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Basic Framework Operations

//  Do nothing for the specified number of ticks.
void pbf_wait(uint16_t ticks);

//  Press the specified button for "hold_ticks" ticks.
//  Then release and wait for "release_ticks" ticks.
void pbf_press_button(Button button, uint16_t hold_ticks, uint16_t release_ticks);

//  Press the specified Dpad button for "hold_ticks" ticks.
//  Then release and wait for "release_ticks" ticks.
void pbf_press_dpad(DpadPosition position, uint16_t hold_ticks, uint16_t release_ticks);

//  Joystick Positions:
//      Neutral     x = 0x80, y = 0x80
//      Up          x = 0x80, y = 0x00
//      Down        x = 0x80, y = 0xff
//      Left        x = 0x00, y = 0x80
//      Right       x = 0xff, y = 0x80
void pbf_move_left_joystick (uint8_t x, uint8_t y, uint16_t hold_ticks, uint16_t release_ticks);
void pbf_move_right_joystick(uint8_t x, uint8_t y, uint16_t hold_ticks, uint16_t release_ticks);

//  Repeatedly press the specified button as quickly as possible for the
//  specified amount of time.
void pbf_mash_button(Button button, uint16_t ticks);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Utilities

//  Wait this many ticks and flash the LEDs.
void start_program_flash(uint16_t ticks);

//  Connect controller from grip menu and go to Switch home.
void grip_menu_connect_go_home(void);

//  Keep the Switch from sleeping after the program finishes.
//  If the Switch sleeps, it may end up restarting the program!
void end_program_loop(void);

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

void end_program_callback       ();

void set_leds                   (PokemonAutomation::PABotBase& device, bool on);
void end_program_callback       (PokemonAutomation::PABotBase& device);

uint32_t system_clock           (PokemonAutomation::PABotBase& device);
void pbf_wait                   (PokemonAutomation::PABotBase& device, uint16_t ticks);
void pbf_press_button           (PokemonAutomation::PABotBase& device, Button button, uint16_t hold_ticks, uint16_t release_ticks);
void pbf_press_dpad             (PokemonAutomation::PABotBase& device, DpadPosition position, uint16_t hold_ticks, uint16_t release_ticks);
void pbf_move_left_joystick     (PokemonAutomation::PABotBase& device, uint8_t x, uint8_t y, uint16_t hold_ticks, uint16_t release_ticks);
void pbf_move_right_joystick    (PokemonAutomation::PABotBase& device, uint8_t x, uint8_t y, uint16_t hold_ticks, uint16_t release_ticks);
void pbf_mash_button            (PokemonAutomation::PABotBase& device, Button button, uint16_t ticks);

void start_program_flash        (PokemonAutomation::PABotBase& device, uint16_t ticks);
void grip_menu_connect_go_home  (PokemonAutomation::PABotBase& device);
void end_program_loop           (PokemonAutomation::PABotBase& device);
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


#define PABB_MSG_COMMAND_PBF_WAIT                   0x80
typedef struct{
    uint8_t seqnum;
    uint16_t ticks;
} PABB_PACK pabb_pbf_wait;

#define PABB_MSG_COMMAND_PBF_PRESS_BUTTON           0x81
typedef struct{
    uint8_t seqnum;
    Button button;
    uint16_t hold_ticks;
    uint16_t release_ticks;
} PABB_PACK pabb_pbf_press_button;

#define PABB_MSG_COMMAND_PBF_PRESS_DPAD             0x82
typedef struct{
    uint8_t seqnum;
    DpadPosition dpad;
    uint16_t hold_ticks;
    uint16_t release_ticks;
} PABB_PACK pabb_pbf_press_dpad;

#define PABB_MSG_COMMAND_PBF_MOVE_JOYSTICK_L        0x83
#define PABB_MSG_COMMAND_PBF_MOVE_JOYSTICK_R        0x84
typedef struct{
    uint8_t seqnum;
    uint8_t x;
    uint8_t y;
    uint16_t hold_ticks;
    uint16_t release_ticks;
} PABB_PACK pabb_pbf_move_joystick;

#define PABB_MSG_COMMAND_MASH_BUTTON                0x85
typedef struct{
    uint8_t seqnum;
    Button button;
    uint16_t ticks;
} PABB_PACK pabb_pbf_mash_button;

#define PABB_MSG_COMMAND_START_PROGRAM_FLASH        0x86
typedef struct{
    uint8_t seqnum;
    uint16_t ticks;
} PABB_PACK pabb_start_program_flash;

#define PABB_MSG_COMMAND_GRIP_MENU_CONNECT_GO_HOME  0x87
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_grip_menu_connect_go_home;

#define PABB_MSG_COMMAND_END_PROGRAM_LOOP           0x88
typedef struct{
    uint8_t seqnum;
} PABB_PACK pabb_end_program_loop;


#if _WIN32
#pragma pack(pop)
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
