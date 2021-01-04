/*  Device Settings
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include "CommonFramework/ControllerDefs.h"
#include "DeviceFramework/HardwareLED.h"
#include "DeviceFramework/DeviceSettings.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Board Type (for LEDs)

//  "BOARD_TYPE = BOARD_TYPE_UNKNOWN" will disable all LEDs.

#if 0
#elif defined __AVR_ATmega16U2__
const int BOARD_TYPE = BOARD_TYPE_UNO;
#elif defined __AVR_ATmega32U4__
const int BOARD_TYPE = BOARD_TYPE_TEENSY2;
#elif defined __AVR_AT90USB1286__
const int BOARD_TYPE = BOARD_TYPE_TEENSY2;
#else
const int BOARD_TYPE = BOARD_TYPE_UNKNOWN;
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  User Callbacks

void start_program_callback(void){
    //  This is run when the program starts. Here you can insert code to
    //  setup output pins.

    //  This callback should return quickly. Do not hang in here for too long
    //  or it will delay the start of the program.

    setup_leds();
}
void end_program_callback(void){
    //  This is run when the program finishes. Here you can insert code to
    //  turn on LEDs or other output pins.

    //  This callback should return quickly. Do not hang in here for too long
    //  or it will prevent the program from entering its safe end-loop.

    onboard_led(true);
}

