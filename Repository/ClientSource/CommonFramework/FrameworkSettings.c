/*  Framework Settings
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include "CommonFramework/ControllerDefs.h"
#include "FrameworkSettings.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  General Options

//  The initial wait period before the program does anything. This gives you
//  time to switch the Arduino from computer to Switch if connected over a KVM.
const uint16_t CONNECT_CONTROLLER_DELAY         =   5 * TICKS_PER_SECOND;

//  Delay from pressing home anywhere in the settings to return to the home menu.
const uint16_t SETTINGS_TO_HOME_DELAY           =   120;

