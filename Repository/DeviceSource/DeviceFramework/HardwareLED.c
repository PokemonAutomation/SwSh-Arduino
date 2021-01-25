/*  Onboard LEDs
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <avr/io.h>
#include "DeviceSettings.h"
#include "HardwareLED.h"

#if 0
#elif (BOARD == BOARD_UNO)
const int leds = (1 << 4) | (1 << 5);
#elif (BOARD == BOARD_PRO_MICRO)
const int leds = (1 << 5);
#elif (BOARD == BOARD_TEENSY2)
const int leds = (1 << 6);
#endif

#if (defined __AVR_ATmega32U4__) || (defined __AVR_AT90USB1286__) || (defined __AVR_ATmega16U2__)
void setup_leds(void){
        #if (BOARD == BOARD_PRO_MICRO) 
            DDRD |= leds;
            onboard_led(false);
            return;
        #elif (BOARD == BOARD_TEENSY2)
            DDRD |= leds;
            onboard_led(false);
            return;
        #elif (BOARD == BARD_UNO)
            DDRD  |= leds;
            PORTD |= leds;
            return;
        #endif
}

void onboard_led(bool on){
    #if (BOARD == BOARD_UNO)
        if (on){
                PORTD &= ~leds;
        }else{
                PORTD |= leds;
        }
        return;
    #else
        if (on){
                PORTD |= leds;
        }else{
                PORTD &= ~leds;
        }
        return;
    #endif
}

#else
void setup_leds(void){}
void onboard_led(bool on){}
#endif
