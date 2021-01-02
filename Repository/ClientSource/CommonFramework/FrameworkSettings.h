/*  Framework Settings
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_FrameworkSettings_H
#define PokemonAutomation_FrameworkSettings_H

#include <stdbool.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  General Options

//  The initial wait period before the program does anything. This gives you
//  time to switch the Arduino from computer to Switch if connected over a KVM.
extern const uint16_t CONNECT_CONTROLLER_DELAY;

//  Delay from pressing home anywhere in the settings to return to the home menu.
extern const uint16_t SETTINGS_TO_HOME_DELAY;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
