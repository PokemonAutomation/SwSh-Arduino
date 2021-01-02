/*  Settings
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 * 
 *  These are global setting shared by all programs.
 * 
 *  You shouldn't need to change any of the timing settings unless you are
 *  encountering problems.
 * 
 */

#include "CommonFramework/ControllerDefs.h"
#include "PokemonSettings.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  General Options

//  Set this to true if starting the game requires checking the internet.
//  Otherwise, programs that require soft-resetting may not work properly.
//
//  If the game is not a physical cartridge and the Switch is not the primary
//  Switch, starting the game will require checking the internet to see if it
//  can be played. If this is the case, set this to true.
//
//  Setting this option to true will slow down soft-resetting by about 3 seconds.
const bool START_GAME_REQUIRES_INTERNET     =   false;

//  Some programs can bypass the system update menu at little performance cost.
//  Setting this to true enables this.
const bool TOLERATE_SYSTEM_UPDATE_MENU_FAST =   true;

//  Some programs can bypass the system update menu, but will take a noticeable
//  performance hit. Setting this to true enables this.
const bool TOLERATE_SYSTEM_UPDATE_MENU_SLOW =   false;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Egg Options

//  true    =   Send Pokemon to boxes is "Automatic".
//  false   =   Send Pokemon to boxes is "Manual".
const bool AUTO_DEPOSIT             =   true;

//  The daycare lady has an extra line of text in Japanese. Set this to true if
//  you are running any of the egg programs in a Japanese game.
const bool EGG_FETCH_EXTRA_LINE     =   false;

//  Time needed to mash B to fetch an egg and return to overworld when
//  auto-deposit is off.
const uint16_t FETCH_EGG_MASH_DELAY =   800;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Den Options

//  Which method to use to bypass the uncatchable Pokemon prompt?
//      true    =   Use a fast (but potentially unreliable) method.
//      false   =   Use a slower (by about 5 seconds) method.
const bool DODGE_UNCATCHABLE_PROMPT_FAST    =   false;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Advanced Options
//
//  You really shouldn't need to touch anything from here on down unless you are
//  encountering problems and are trying to debug it yourself.
//

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  General Timings

//  Time to accept FRs before returning to den lobby.
const uint16_t AUTO_FR_DURATION                 =   8 * TICKS_PER_SECOND;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Menu Navigation Timings

//  Delay to bring up the menu when pressing X in the overworld.
const uint16_t OVERWORLD_TO_MENU_DELAY          =   120;

//  Delay to go from menu back to overworld.
const uint16_t MENU_TO_OVERWORLD_DELAY          =   250;

//  Delay from pressing home to entering the the Switch home menu.
//  This affects the speed of date-spamming programs (i.e. watt farmer)
const uint16_t GAME_TO_HOME_DELAY_FAST          =   100;
const uint16_t GAME_TO_HOME_DELAY_SAFE          =   125;


//  Delay to enter game from home menu.
const uint16_t HOME_TO_GAME_DELAY               =   3 * TICKS_PER_SECOND;

//  Time needed to open Y-COMM.
const uint16_t OPEN_YCOMM_DELAY                 =   200;

//  Delay to enter your Switch profile.
const uint16_t ENTER_PROFILE_DELAY              =   2 * TICKS_PER_SECOND;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Start Game Timings

//  If starting the game requires checking the internet, wait this long for it.
const uint16_t START_GAME_INTERNET_CHECK_DELAY  =   3 * TICKS_PER_SECOND;

//  Delays to start and enter the game when it isn't running.
const uint16_t START_GAME_MASH                  =   2 * TICKS_PER_SECOND;   //  1. Mash A for this long to start the game.
const uint16_t START_GAME_WAIT                  =   20 * TICKS_PER_SECOND;  //  2. Wait this long for the game to load.
const uint16_t ENTER_GAME_MASH                  =   3 * TICKS_PER_SECOND;   //  3. Mash A for this long to enter the game.
const uint16_t ENTER_GAME_WAIT                  =   11 * TICKS_PER_SECOND;  //  4. Wait this long for the game to enter the overworld.


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Den Timings

//  Time needed to enter a den on final button press.
const uint16_t ENTER_OFFLINE_DEN_DELAY      =   125;

//  Time from exiting den after a day-skip to when you can collect watts and re-enter it.
const uint16_t REENTER_DEN_DELAY            =   5 * TICKS_PER_SECOND;

//  Time needed to collect watts.
const uint16_t COLLECT_WATTS_OFFLINE_DELAY  =   80;
const uint16_t COLLECT_WATTS_ONLINE_DELAY   =   3 * TICKS_PER_SECOND;

//  Time needed to bypass uncatchable pokemon prompt.
const uint16_t UNCATCHABLE_PROMPT_DELAY     =   110;

//  Time needed to open a den lobby on local connection.
const uint16_t OPEN_LOCAL_DEN_LOBBY_DELAY   =   3 * TICKS_PER_SECOND;

//  Time needed to enter Switch Pokemon.
const uint16_t ENTER_SWITCH_POKEMON         =   4 * TICKS_PER_SECOND;

//  Time needed to exit Switch Pokemon back to den lobby.
const uint16_t EXIT_SWITCH_POKEMON          =   3 * TICKS_PER_SECOND;

//  Always 3 minutes.
const uint16_t FULL_LOBBY_TIMER             =   180 * TICKS_PER_SECOND;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Box Timings (for egg programs)

const uint16_t BOX_SCROLL_DELAY        =    20;     //  Delay to move the cursor.
const uint16_t BOX_CHANGE_DELAY        =    80;     //  Delay to change boxes.
const uint16_t BOX_PICKUP_DROP_DELAY   =    90;     //  Delay to pickup/drop pokemon.

const uint16_t MENU_TO_POKEMON_DELAY   =    300;    //  Delay to enter Pokemon menu.
const uint16_t POKEMON_TO_BOX_DELAY    =    300;    //  Delay to enter box system.
const uint16_t BOX_TO_POKEMON_DELAY    =    250;    //  Delay to exit box system.
const uint16_t POKEMON_TO_MENU_DELAY   =    250;    //  Delay to return to menu.

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
