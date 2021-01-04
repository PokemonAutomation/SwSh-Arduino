/*  Onboard LEDs
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <avr/io.h>
#include "DeviceSettings.h"
#include "HardwareLED.h"

#if (defined __AVR_ATmega32U4__) || (defined __AVR_AT90USB1286__)
void setup_leds(void){
    switch (BOARD_TYPE){
    case BOARD_TYPE_TEENSY2:
        DDRD |= (1<<6);
        onboard_led(false);
        return;
    }
}
void onboard_led(bool on){
    switch (BOARD_TYPE){
    case BOARD_TYPE_TEENSY2:
        if (on){
            PORTD |= (1<<6);
        }else{
            PORTD &= ~(1<<6);
        }
        return;
    }
}

#elif defined __AVR_ATmega16U2__
void setup_leds(void){
    switch (BOARD_TYPE){
    case BOARD_TYPE_UNO:{
        const int leds = (1 << 4) | (1 << 5);
        DDRD  |= leds;
        PORTD |= leds;
        return;
    }
    }
}
void onboard_led(bool on){
    switch (BOARD_TYPE){
    case BOARD_TYPE_UNO:{
        const int leds = (1 << 4) | (1 << 5);
        if (on){
            PORTD &= ~leds;
        }else{
            PORTD |= leds;
        }
        return;
    }
    }
}

#else
void setup_leds(void){}
void onboard_led(bool on){}
#endif

